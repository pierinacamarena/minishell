/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:21 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/04 13:31:31 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_var_list(t_env_list **begin, char *var)
{
	t_env_list	*curr;
	t_env_list	*new;

	new = ft_set_node(var);
	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	else
	{
		curr = *begin;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

void	export_check_list(t_shell *shell, char *var)
{
	char		**split;
	char		*empty_var;
	t_env_list	*aux;

	if (ft_strchr(var, '=') != NULL)
	{
		if (key_exists(shell->env, var) == 0)
		{
			add_var_list(&shell->env, var);
			add_var_list(&shell->exp, var);
			return ;
		}
		else if (key_exists(shell->env, var) == 1)
		{
			if (same_value(shell->env, var) == 0)
			{
				split = ft_split(var, '=');
				split[0] = ft_strjoin(split[0], "=");
				find_replace(&shell->env, split[0], split[1]);
				find_replace(&shell->exp, split[0], split[1]);
				ft_free(split);
				return ;
			}
			else if (same_value(shell->env, var) == 1)
				return ;
		}
	}
	else
	{
		empty_var = ft_strjoin(var, "=");
		if (key_exists(shell->exp, empty_var))
		{
			if (key_exists(shell->env, empty_var))
				return ;
			else
			{
				empty_var = ft_strjoin(var, "=");
				aux = ft_set_node(empty_var);
				ft_add_node(&shell->env, aux);
				free(empty_var);
			}
		}
		else
		{
			empty_var = ft_strjoin(empty_var, "=''");
			aux = ft_set_node(empty_var);
			ft_add_node(&shell->exp, aux);
			free(empty_var);
		}
	}
}

void	ft_export_list(t_shell *shell, t_pipeline *data, int *read_write_fds)
{
	int	i;

	if (!data->command)
		return ;
	if (array_size(data->command) == 1)
		ft_env(shell->exp, read_write_fds);
	else
	{
		i = 1;
		while (data->command[i])
		{
			export_check_list(shell, data->command[i]);
			i++;
		}
	}
}
