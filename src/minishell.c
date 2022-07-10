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

char *ft_prompt(char const *str)
{
    char    *prompt;

    prompt = readline(str);
    return (prompt);
}

int check_builtin(char *cmd)
{
    int is_built;

    is_built = 0;
    // if (ft_strcmp(cmd, "echo") == 0)
    // {
    //     ft_echo();
    //     is_built = 1;
    // }
    // else if (ft_strcmp(cmd, "pwd") == 0)
    // {
    //     ft_pwd();
    //     is_built = 1;
    // }
    // else if (ft_strcmp(cmd, "env") == 0)
    // {
    //     ft_env(env);
    //     is_built = 1;
    // }
    if (ft_strcmp(cmd, "exit") == 0)
    {
        ft_exit(0, cmd);
    }
    else
        is_built = 0;
    return (is_built);
}

int main(void)
{
    char    *str;
    int     built_in;

    str = NULL;
    while (1)
    {
        str = ft_prompt(PROMPT_NAME);
        built_in = check_builtin(str);
        if (built_in == 0)
            printf("%s\n", str);
        if (str)
            free(str);
    }
    return (1);
}