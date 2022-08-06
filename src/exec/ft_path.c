/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 19:00:08 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 15:22:50 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(const char *target)
{
	struct stat	statbuf;

	stat(target, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

char	*ft_path(char *arg, char **env)
{
	int		i;
	char	*cmd;
	char	**path_split;

	if (!is_dir(arg) && access(arg, X_OK) == 0)
		return (ft_strdup(arg));
	i = 0;
	while (env[i])
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
	if (cmd)
		return (cmd);
	ft_free(path_split);
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
		if (!is_dir(arg) && access(cmd, X_OK) == 0)
		{
			ft_free(path_split);
			return (cmd);
		}
		free(cmd);
		i++;
	}
	return (NULL);
}
