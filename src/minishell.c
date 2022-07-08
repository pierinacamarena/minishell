/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:52:54 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 18:54:58 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_prompt(char *str)
{
    printf("minishell:%s$\n", str);
}

int main(void)
{
    int loop;
    char *env;

    loop = 1;
    while(loop)
    {
        env = getcwd(NULL, 0);
        ft_prompt(env);
        exit (1);
    }
    return (0);
}