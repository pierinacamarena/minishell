/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:52:54 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/04 17:14:07 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_code;
/*
Function that prints the minishell prompt using the allowed builtin function
called readline()
*/

char *ft_prompt(char const *str)
{
    char    *prompt;

    prompt = readline(str);
	add_history(prompt);
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
    t_shell     		shell;
	t_scanner			scanner;
	char        		*str;
	struct sigaction	act;

    str = NULL;
	if (ac > 1)
	{	
		printf("too many arguments\n");
		return (1);
	}
	(void)av;
	set_env_exp(&shell, env);
	while (1)
	{
		act.sa_handler = sighandler;
		sigaction(SIGINT, &act, NULL);
		act.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &act, NULL);
		str = ft_prompt(PROMPT_NAME);
		if (str == NULL)
		{
			printf("\n");
			//free the env
			exit(EXIT_SUCCESS);
		}
		if (str)
		{
			init_scanner(&scanner, str);
			parse(&scanner, &shell);
		}
		if (str && *str)
			free(str);
	}
    return (0);
}
