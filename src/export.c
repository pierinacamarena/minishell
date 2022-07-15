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


void    add_var_env(t_env_list **begin, char *var)
{
    t_env_list  *curr;
    t_env_list  *new;

    printf("hereheere\n");
    new = ft_set_node(var);
    if (*begin == NULL)
    {
        printf("NULLLLL\n");
        *begin = new;
        return ;
    }
    else
    {    
        curr = *begin;
        while (curr->next != NULL)
            curr = curr->next;
        printf("%s\n%s\n", new->node->key, new->node->content);
        printf("%s\n%s\n", curr->node->key, curr->node->content);
        curr->next = new;
        printf("%s\n%s\n", curr->next->node->key, curr->next->node->content);
    }
}

// void    add_var_exp(t_exp_list **begin)
// {

// }

void    ft_export(t_shell *shell, char **env)
{
    char        **arr;
    int         i;

    if(!shell->cmds)
        return ;
    arr = sorted_exp(env);
    shell->exp = init_exp(arr);
    ft_free(arr);
    if (array_size(shell->cmds) == 1)
        ft_print_export(shell->exp);
    else
    {
        printf("here\n");
        i = 1;
        while (shell->cmds[i])
        {
            add_var_env(&shell->env, shell->cmds[i]);
            i++;
        }
        ft_print_list(shell->env);
    }

}