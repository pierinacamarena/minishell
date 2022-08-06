/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:00:08 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 20:51:27 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(const char *target)
{
	struct stat	statbuf;

	ft_memset(&statbuf, 0, sizeof(statbuf));
	stat(target, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

char	*get_cmd(char **env, char *arg)
{
	char	**path_split;
	char	*cmd;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
		return (NULL);
	path_split = ft_split(env[i] + 5, ':');
	if (path_split == NULL)
		return (NULL);
	cmd = cmd_tester(path_split, arg);
	ft_free(path_split);
	return (cmd);
}

char	*ft_path(char *arg, char **env)
{
	char	*cmd;

	if (!is_dir(arg) && access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	else if (access(arg, F_OK) == 0)
	{
		g_exit_code = 126;
		return (NULL);
	}
	cmd = get_cmd(env, arg);
	if (cmd && !is_dir(cmd) && access(cmd, X_OK) == 0)
		return (cmd);
	else if (cmd && !is_dir(cmd))
		g_exit_code = 126;
	return (NULL);
}

char	*cmd_tester(char **path_split, char *arg)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	while (path_split[i])
	{
		j = ft_strlen(path_split[i]) - 1;
		if (path_split[i][j] == '/')
			cmd = ft_strjoin(path_split[i], arg);
		else
			cmd = ft_str3join(path_split[i], "/", arg);
		if (!is_dir(arg) && access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}
