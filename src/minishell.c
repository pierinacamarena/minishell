/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:52:54 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 19:42:33 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Function that prints the minishell prompt using the allowed builtin function
called readline()
*/

char *ft_prompt(char const *str)
{
    char    *prompt;

    prompt = readline(str);
    return (prompt);
}


void    set_env_exp(t_shell *shell, char **env)
{
    char **arr;
	arr = sorted_exp(env);
    if (!arr)
        return ;   
    shell->env = init_env(env);
    shell->exp = init_env(arr);
	shell->env_exec = 0;
    ft_free(arr);
}

int main(int ac, char **av, char **env)
{
    t_shell     shell;
	t_scanner	scanner;
    char        *str;

    str = NULL;
    if (ac == 1)
    {
        (void)av;
        set_env_exp(&shell, env);
        while (1)
        {
            (void)av;
			signal(SIGINT, sighandler);
            str = ft_prompt(PROMPT_NAME);
			init_scanner(&scanner, str);
			parse(&scanner, &shell);
			if (str && *str)
				free(str);
        }
    }
    return (1);
}