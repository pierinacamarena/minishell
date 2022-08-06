/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:15 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 21:37:04 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_cmds_list(char **cmds)
{
	int	len;

	len = 0;
	while (cmds[len])
		len++;
	return (len);
}

int	cd_helper(t_shell *shell)
{
	char	*saved_oldpwd;
	char	*new_pwd;
	char	*home_val;

	home_val = ft_getenv(shell->env, "HOME");
	if (home_val == NULL)
		return (1);
	else if (*home_val == '\n')
		return (0);
	saved_oldpwd = getcwd(NULL, 0);
	chdir(home_val);
	new_pwd = getcwd(NULL, 0);
	find_replace(&shell->env, "OLDPWD=", saved_oldpwd);
	find_replace(&shell->env, "PWD=", new_pwd);
	find_replace(&shell->exp, "OLDPWD=", saved_oldpwd);
	find_replace(&shell->exp, "PWD=", new_pwd);
	free(saved_oldpwd);
	free(new_pwd);
	return (0);
}

int	cd_helper_two(t_pipeline *data, t_shell *shell)
{
	char	*saved_oldpwd;
	char	*new_pwd;

	saved_oldpwd = getcwd(NULL, 0);
	if (chdir(data->command[1]) == -1)
	{
		free(saved_oldpwd);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->command[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	find_replace(&shell->env, "OLDPWD=", saved_oldpwd);
	find_replace(&shell->env, "PWD=", new_pwd);
	find_replace(&shell->exp, "OLDPWD=", saved_oldpwd);
	find_replace(&shell->exp, "PWD=", new_pwd);
	free(saved_oldpwd);
	free(new_pwd);
	return (0);
}

int	cd_dash(t_pipeline *data, t_shell *shell)
{
	char	*saved_oldpwd;
	char	*new_pwd;

	saved_oldpwd = getcwd(NULL, 0);
	if (chdir(ft_getenv(shell->env, "OLDPWD")) == -1)
	{
		free(saved_oldpwd);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(data->command[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	find_replace(&shell->env, "OLDPWD=", saved_oldpwd);
	find_replace(&shell->env, "PWD=", new_pwd);
	find_replace(&shell->exp, "OLDPWD=", saved_oldpwd);
	find_replace(&shell->exp, "PWD=", new_pwd);
	free(saved_oldpwd);
	free(new_pwd);
	return (0);
}

int	ft_cd_list(t_shell *shell, t_pipeline *data)
{
	int		len;

	if (!data->command)
		return (-1);
	len = len_cmds_list(data->command);
	if (len > 2)
	{
		write_error("minishell: cd: too many arguments\n");
		return (1);
	}
	else if (len == 1)
		return (cd_helper(shell));
	else
	{
		if (ft_strcmp(data->command[1], "~") == 0)
			return (cd_helper(shell));
		else if (ft_strcmp(data->command[1], "-") == 0)
			return (cd_dash(data, shell));
		else
			return (cd_helper_two(data, shell));
	}
}
