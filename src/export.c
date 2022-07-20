/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:32:28 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/15 21:32:29 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    add_var(t_env_list **begin, char *var)
{
    t_env_list  *curr;
    t_env_list  *new;

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

void    export_check(t_shell *shell, char *var)
{
    char		**split;
	char		*empty_var;
	t_env_list	*aux;

    if (ft_strchr(var, '=') != NULL)
    {
		if (key_exists(shell->env, var) == 0)
		{
			add_var(&shell->env, var);
			add_var(&shell->exp, var);
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
				return;
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

void    ft_export(t_shell *shell)
{
    int     i;

    if(!shell->cmds)
        return;
    if (array_size(shell->cmds) == 1)
    {
		ft_print_list(shell->exp);
	}
    else
    {
        i = 1;
        while (shell->cmds[i])
        {
			export_check(shell, shell->cmds[i]);
            i++;
        }
    }

}