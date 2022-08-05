/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:21 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/05 21:39:50 by pcamaren         ###   ########.fr       */
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

void	export_check_helper(t_shell *shell, char *var)
{
	char	**split;

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

void	export_check_helper_two(t_shell *shell, char *empty_var)
{
	t_env_list	*aux;

	empty_var = ft_strjoin(empty_var, "=''");
	aux = ft_set_node(empty_var);
	ft_add_node(&shell->exp, aux);
	free(empty_var);
}

void	export_check_list(t_shell *shell, char *var)
{
	char		*empty_var;
	t_env_list	*aux;

	if (ft_strchr(var, '=') != NULL)
		export_check_helper(shell, var);
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
			export_check_helper_two(shell, empty_var);
	}
}

int	export_error_helper(char *arg)
{
	if (ft_strcmp(arg, "$") == 0)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	else if (ft_strcmp(arg, "") == 0)
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (2);
	}
	return (0);
}

int	ft_export_error(char *arg)
{
	int	error;

	if (ft_strcmp(arg, "=") == 0)
	{
		write_error("export: `=': not a valid identifier");
		return (1);
	}
	else if (arg[0] == '=')
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	error = export_error_helper(arg);
	return (error);
}

int	ft_export_list(t_shell *shell, t_pipeline *data, int *read_write_fds)
{
	int	i;
	int	error;

	if (array_size(data->command) == 1)
		ft_env(shell->exp, read_write_fds);
	else
	{
		i = 1;
		while (data->command[i])
		{
			error = ft_export_error(data->command[i]);
			if (error == 1)
				return (1);
			else if (error == 2)
			{
				if (!data->command[i + 1])
					return (1);
				i++;
			}
			export_check_list(shell, data->command[i]);
			i++;
		}
	}
	return (0);
}
