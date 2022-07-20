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
        printf("still not handled :] \n");
		//should take me to home
        return (1);
    }
    else
    {
        // env = getcwd(NULL, 0);
		//search if the directory exists
		//if it exists 
			//save the current pwd as SAVED_OLDPWD = currentpwd
			SAVED_OLDPWD = getcwd(NULL, 0);
        	chdir(shell->cmds[1]);
			NEW_PWD = getcwd(NULL, 0);
			//funcion que cambia el content
			find_replace(&shell->env, "OLDPWD=", SAVED_OLDPWD);
			find_replace(&shell->env, "PWD=", NEW_PWD);
			find_replace(&shell->exp, "OLDPWD=", SAVED_OLDPWD);
			find_replace(&shell->exp, "PWD=", NEW_PWD);
			// printf("SAVED_OLDPWD is: %s\n", SAVED_OLDPWD);
			// printf("NEW_PWD is: %s\n", NEW_PWD);
			//NEW_PWD = pwd  (after the chdir)
			//PWD = NEW_PWD
			//replace OLDPWD = SAVED_OLDPWD
        return (0);
    }
}