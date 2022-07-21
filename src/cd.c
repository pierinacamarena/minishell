/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:14:20 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 23:14:22 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int len_cmds(char **cmds)
{
    int len;

    len = 0;
    while(cmds[len])
    {
        len++;
    }
    return (len);
}

int ft_cd(t_shell *shell)
{
    int     len;
    char    *SAVED_OLDPWD;
	char	*NEW_PWD;
	// char	*home;

    if (!shell->cmds)
        return (-1);
    len = len_cmds(shell->cmds);
    if (len > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return (-1);
    }
    else if (len == 1)
    {
		SAVED_OLDPWD = getcwd(NULL, 0);
		// home = getenv("HOME");
		chdir(getenv("HOME"));
		// free(home);
		NEW_PWD = getcwd(NULL, 0);
        find_replace(&shell->env, "OLDPWD=", SAVED_OLDPWD);
		find_replace(&shell->env, "PWD=", NEW_PWD);
		find_replace(&shell->exp, "OLDPWD=", SAVED_OLDPWD);
		find_replace(&shell->exp, "PWD=", NEW_PWD);
        free(SAVED_OLDPWD);
        free(NEW_PWD);
        return (1);
    }
    else
    {
        if (ft_strcmp(shell->cmds[1], "~") == 0)
        {
            SAVED_OLDPWD = getcwd(NULL, 0);
			// home = getenv("HOME");
			chdir(getenv("HOME"));
			// free(home);
		    NEW_PWD = getcwd(NULL, 0);
            find_replace(&shell->env, "OLDPWD=", SAVED_OLDPWD);
		    find_replace(&shell->env, "PWD=", NEW_PWD);
		    find_replace(&shell->exp, "OLDPWD=", SAVED_OLDPWD);
		    find_replace(&shell->exp, "PWD=", NEW_PWD);
            free(SAVED_OLDPWD);
            free(NEW_PWD);
            return (1);
        }
        else
        {
			SAVED_OLDPWD = getcwd(NULL, 0);
        	if (chdir(shell->cmds[1]) == -1)
            {
                free(SAVED_OLDPWD);
                printf("minishell: cd: %s: No such file or directory\n", shell->cmds[1]);
            }
			NEW_PWD = getcwd(NULL, 0);
			find_replace(&shell->env, "OLDPWD=", SAVED_OLDPWD);
			find_replace(&shell->env, "PWD=", NEW_PWD);
			find_replace(&shell->exp, "OLDPWD=", SAVED_OLDPWD);
			find_replace(&shell->exp, "PWD=", NEW_PWD);
            free(SAVED_OLDPWD);
            free(NEW_PWD);
            return (0);
        }
    }
}
