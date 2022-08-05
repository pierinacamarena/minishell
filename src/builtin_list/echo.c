/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:22:14 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/05 13:05:09 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	num_args(char **args)
{
	int	num;

	num = 0;
	while (args[num] != NULL)
		num++;
	return (num);
}

int	ft_isn(char *str)
{
	int	i;
	int	len;

	i = 1;
	if (str)
	len = ft_strlen(str);
	if (str[0] == '-')
	{
		while (str[i] == 'n' && i < len)
			i++;
		if (i == len)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	echo_helper(char **args, int len, int *read_write_fds)
{
	int	i;
	int	is_n;

	i = 1;
	is_n = 0;
	while (args[i] && (ft_isn(args[i]) == 1))
	{
		is_n = 1;
		i++;
	}
	while (args[i] && i < (len - 1))
	{
		write(read_write_fds[1], args[i], ft_strlen(args[i]));
		write(read_write_fds[1], " ", 1);
		i++;
	}
	if (args[i])
		write(read_write_fds[1], args[i], ft_strlen(args[i]));
	return (is_n);
}

int	ft_echo(char **args, int *read_write_fds)
{
	int	len;
	int	is_n;

	is_n = 0;
	len = num_args(args);
	if (len == 1)
	{
		write(read_write_fds[1], "\n", 1);
		return (0);
	}
	if (len > 1)
		is_n = echo_helper(args, len, read_write_fds);
	if (is_n == 0)
		write(read_write_fds[1], "\n", 1);
	return (0);
}
