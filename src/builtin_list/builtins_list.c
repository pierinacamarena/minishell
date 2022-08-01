/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:11 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 01:34:47 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_exit_list(long long i, t_shell *shell, t_list *data)
{
    //free anything allocated once we are more advanced in the project :P
    ft_free_list(&shell->env);
    ft_free_list(&shell->exp);
    ft_free(shell->cmds);
	list_clear(&data);
    if (i <= INT_MAX || i >= INT_MIN)
        exit(i);
}