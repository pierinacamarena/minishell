/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:15 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 17:03:21 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int len_cmds_list(char **cmds)
{
    int len;

    len = 0;
    while(cmds[len])
    {
        len++;
    }
    return (len);
}

int ft_cd_list(t_shell *shell, t_pipeline *data)
{
    int     len;
    char    *SAVED_OLDPWD;
	char	*NEW_PWD;

    if (!data->command)
        return (-1);
    len = len_cmds_list(data->command);
    if (len > 2)
    {
        write_error("minishell: cd: too many arguments");
        return (-1);
    }
    else if (len == 1)
    {
		SAVED_OLDPWD = getcwd(NULL, 0);
		chdir(ft_getenv(shell->env, "HOME"));
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
        if (ft_strcmp(data->command[1], "~") == 0)
        {
            SAVED_OLDPWD = getcwd(NULL, 0);
			chdir(ft_getenv(shell->env, "HOME"));
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
        	if (chdir(data->command[1]) == -1)
            {
                free(SAVED_OLDPWD);
				ft_putstr_fd("minishell: cd: ", 2);
				ft_putstr_fd(data->command[1], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return (-1);
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
