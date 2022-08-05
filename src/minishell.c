/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:52:54 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/05 15:40:59 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;
/*
Function that prints the minishell prompt using the allowed builtin function
called readline()
*/

char	*ft_prompt(char const *str)
{
	char	*prompt;

	prompt = readline(str);
	add_history(prompt);
	return (prompt);
}

void	set_env_exp(t_shell *shell, char **env)
{
	char	**arr;

	arr = sorted_exp(env);
	if (!arr)
		return ;
	shell->env = init_env(env);
	shell->exp = init_env(arr);
	shell->env_exec = 0;
	ft_free(arr);
}

void	exit_on_eof(char *prompt, t_shell *shell)
{
	printf("\n");
	free(prompt);
	free_exit(0, shell, NULL, ENV | HIST);
}

int	main(int ac, char **av, char **env)
{
	t_shell		shell;
	t_scanner	scanner;
	char		*str;

	(void)av;
	str = NULL;
	if (ac > 1)
		print_exit(1, "too many arguments\n");
	set_env_exp(&shell, env);
	while (1)
	{
		siginit(SIGINT, sighandler);
		siginit(SIGQUIT, SIG_IGN);
		str = ft_prompt(PROMPT_NAME);
		if (str == NULL)
			exit_on_eof(str, &shell);
		init_scanner(&scanner, str);
		parse(&scanner, &shell);
		if (*str)
			free(str);
	}
	return (0);
}
