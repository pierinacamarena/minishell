/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:54:51 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/05 11:37:52 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sighandler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\b \b\b \b\n", 7);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	exit_code = 128 + signum;
}

void	siginit(int signum, void (*sighandler)(int))
{
	struct sigaction	act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = sighandler;
	sigemptyset(&act.sa_mask);
	sigaction(signum, &act, NULL);
}
