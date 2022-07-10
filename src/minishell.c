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
#include <readline/readline.h>
#include <readline/history.h>


// void    ft_prompt(char *str)
// {
//     printf("minishell:%s%% ", str);
// }

// int main(void)
// {
//     char    *env;
//     char    *line;
//     int     gnl;

//     while(1)
//     {
//         env = getcwd(NULL, 0);
//         ft_prompt(env);
//         if ((gnl = get_next_line(0, &line)) == -1)
//             return (1);
//         printf("%s\n", line);
//         free(line);
//     }
//     return (0);
// }

char *ft_prompt(char const *str)
{
    char    *prompt;

    prompt = readline(str);
    return (prompt);
}

int main(void)
{
    char *str;

    str = NULL;
    while (1)
    {
        str = ft_prompt(PROMPT_NAME);
        printf("%s\n", str);
        if (str)
            free(str);
    }
    return (1);
}