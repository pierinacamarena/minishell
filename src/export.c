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
    char	**split;
	char	*empty_var;

    if (ft_strchr(var, '=') != NULL)
    {
		printf("inside condition where = exists\n");
		if (key_exists(shell, var) == 0)
		{
			add_var(&shell->env, var);
			add_var(&shell->exp, var);
			return ;
        }
        else if (key_exists(shell, var) == 1)
		{
			if (same_value(shell, var) == 0)
			{
				printf("case when we change the content of an existing variable\n");
				// split = ft_split(var, '=');
				// find_replace(&shell->env, split[0], split[1]);
				// find_replace(&shell->exp, split[0], split[1]);
				// ft_free(split);
				return ;
			}
			else if (same_value(shell, var) == 1)
			{
				printf("case where the variable exits with the same content\n");
				return ;
			}
		}
	}
	else
	{
		if (key_exists(shell->exp, empty_var))
		{
			printf("case where the variable exists on export\n");
			// empty_var = ft_strjoin(var, "=");
			// ft_add_node(&shell->env, empty_var);
			// free(empty_var);
		}
		else
		{
			printf("case where the variable does not exist inside export\n");
			// empty_var = ft_strjoin(empty_var, "=''");
			// ft_add_node(&shell->exp, empty_var);
			// free(empty_var);
		}
	}
}

void    ft_export(t_shell *shell)
{
    int     i;

    if(!shell->cmds)
        return;
    if (array_size(shell->cmds) == 1)
        ft_print_list(shell->exp);
    else
    {
        i = 1;
        while (shell->cmds[i])
        {
			export_check(shell, shell->cmds[i]);
            // add_var(&shell->env, shell->cmds[i]);
            // add_var(&shell->exp, shell->cmds[i]);
            i++;
        }
    }

}