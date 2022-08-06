/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_list_builtin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:21 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 15:49:38 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*setnode_helper_export(t_env_list *list, t_env *node_env, char *info_one, char *info_two)
{
	list->node = node_env;
	list->node->key = ft_strdup(info_one);
	if (!info_two)
		list->node->content = NULL;
	else
		list->node->content = ft_strdup(info_two);
	list->next = NULL;
	return (list);
}

t_env_list	*ft_set_node_export(char *env)
{
	char		*info_one;
	char		*info_two;
	t_env_list	*list;
	t_env		*node_env;
	int			i;
	
	i = 0;
	if (!env)
		return (NULL);
	while (env[i] != '=')
		i++;
	info_one = ft_substr(env, 0, i + 1);
	info_two = ft_substr(env, i + 1, ft_strlen(env));
	list = malloc(sizeof(t_env_list));
	if (!list)
		return (NULL);
	node_env = malloc(sizeof(t_env));
	if (!node_env)
		return (NULL);
	setnode_helper_export(list, node_env, info_one, info_two);
	free(info_one);
	free(info_two);
	return (list);
}

void	add_var_list(t_env_list **begin, char *var)
{
	t_env_list	*curr;
	t_env_list	*new;

	new = ft_set_node_export(var);
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

void	split_export(t_shell *shell, char *var)
{
	char	*info_one;
	char	*info_two;
	int		i;

	i = 0;

	while (var[i] != '=')
		i++;
	info_one = ft_substr(var, 0, i + 1);
	info_two = ft_substr(var, i + 1, ft_strlen(var));
	find_replace(&shell->env, info_one, info_two);
	find_replace(&shell->exp, info_one, info_two);
	free(info_one);
	free(info_two);
}

void	export_check_helper(t_shell *shell, char *var)
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
			split_export(shell, var);
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
	else if (ft_isdigit(arg[0]))
	{
		ft_putstr_fd("export: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	ft_export_error(char *arg)
{
	int	error;

	if (ft_strcmp(arg, "=") == 0)
	{
		write_error("export: `=': not a valid identifier\n");
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

	error = 0;
	if (array_size(data->command) == 1)
		ft_env(shell->exp, read_write_fds);
	else
	{
		i = 1;
		while (data->command[i])
		{
			error = ft_export_error(data->command[i]);
			if (error == 1)
				return (error);
			else if (error == 2)
			{
				if (!data->command[i++ + 1])
					return (1);
				error = 1;
			}
			export_check_list(shell, data->command[i]);
			i++;
		}
	}
	return (error);
}
