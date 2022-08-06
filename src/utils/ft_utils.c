/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:46:18 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 20:11:38 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static int	size_int(int n)
{
	int	size;

	size = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	int		neg;
	char	*nb_arr;

	neg = 0;
	if (n < 0)
		neg = 1;
	size = size_int(n) + neg;
	nb_arr = malloc(sizeof(char) * (size + 1));
	if (!nb_arr)
		return (0);
	if (neg)
		nb_arr[0] = '-';
	nb_arr[size] = '\0';
	while (size > neg)
	{
		nb_arr[size - 1] = (n % 10) * (1 - (2 * neg)) + '0';
		n /= 10;
		size--;
	}
	return (nb_arr);
}

void	full_free(t_shell *shell, t_pipeline *data)
{
	if (shell->env_exec)
		ft_free(shell->env_exec);
	ft_free_list(&shell->env);
	ft_free_list(&shell->exp);
	free_commands_list(data);
}
