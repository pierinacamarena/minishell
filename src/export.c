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


void    ft_export(t_shell *shell)
{

    //add functionality when they put export var with no =
    //and when they put export var with no = again
    //so that it adds it as var=
    //and export adds it ad var='' at the first time

    //add that if the variable already exits it wont do anything
    //add that if the variable exists but the new export has a different
    //content
    int         i;

    if(!shell->cmds)
        return;
    if (array_size(shell->cmds) == 1)
        ft_print_list(shell->exp);
    else
    {
        i = 1;
        while (shell->cmds[i])
        {
            add_var(&shell->env, shell->cmds[i]);
            add_var(&shell->exp, shell->cmds[i]);
            i++;
        }
    }

}