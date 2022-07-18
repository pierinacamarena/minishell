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

int     key_exists(t_shell *shell, char *var)
{
    char        **var_split;
    t_env_list  *curr;
    char        *temp;

    if (!var)
        return (-1);
    var_split = ft_split(var, '=');
	temp = ft_strjoin(var_split[0], "=");
	free(var_split[0]);
	var_split[0] = temp;

    curr = shell->env;
    while (curr->next != NULL)
    {
        if (ft_strcmp(curr->node->key, var_split[0]) == 0)
        {
            ft_free(var_split);
            return (1);
        }
        curr = curr->next;
    }
    ft_free(var_split);
    return (0);
}

int     same_value(t_shell *shell, char *var)
{
    char        **var_split;
    t_env_list  *curr;

    if (shell->env == NULL)
        return (0);
    if (!var)
        return (-1);
    var_split = ft_split(var, '=');
    curr = shell->env;
    while (curr->next != NULL)
    {
        if (ft_strcmp(curr->node->content, var_split[1]) == 0)
        {
            ft_free(var_split);
            return (1);
        }
        curr = curr->next;
    }
    ft_free(var_split);
    return (0);
}

void    export_check(t_shell *shell, char *var)
{
    char **split;

    if (ft_strchr(var, '=') == 0)
            {
                if (key_exists(shell, var) == 0)
                {
                    add_var(&shell->env, var);
                    add_var(&shell->exp, var);
                    i++;
                }
                else if (key_exists(shell, var) == 1)
                {
                    if (same_value(shell, var) == 0)
                    {
                        char    *new;
                        split = ft_split(var, '=');
                        new = ft_strdup(split[1]);
                        ft_free(split);
                        //find node and replace
                        //in both env and export
                        free(new);
                        i++;
                    }
                    else if (same_value(shell, var) == 1)
                        return ;
                }
            }
            else
            {
                if (repeat == 0)
                {
                    repeat++;
                    //add to export like this var=''
                    i++;
                }
                else if repeat == 1
                {
                    repeatt+
                    //add to env like this var= 
                    i++;
                }
                else
                {
                    //do nothing;
                    i++;
                }
            }
}

void    ft_export(t_shell *shell)
{
    int     repeat;
    int     i;

    repeat = 0;
    if(!shell->cmds)
        return;
    if (array_size(shell->cmds) == 1)
        ft_print_list(shell->exp);
    else
    {
        i = 1;
        while (shell->cmds[i])
        {
            
        }
    }

}