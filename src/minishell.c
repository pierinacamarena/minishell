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
    printf("minishell:%s %%", str);
}

int main(void)
{
    char    *env;
    char    *line;
    int     gnl;

    while(1)
    {
        env = getcwd(NULL, 0);
        ft_prompt(env);
        if ((gnl = get_next_line(0, &line)) == -1)
            return (1);
        printf("%s\n", line);
        free(line);
    }
    return (0);
}