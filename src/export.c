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

void ft_export(t_shell *shell, char **env)
{
    char        **arr;

    if(!shell->cmds)
        return ;
    arr = sorted_exp(env);
    shell->exp = init_exp(arr);
    ft_free(arr);
    if (array_size(shell->cmds) == 1)
    {
        ft_print_export(shell->exp);
    }
    else
    {
        printf("still not handled\n");
    }

}