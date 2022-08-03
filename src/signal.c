/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:54:51 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/03 18:22:16 by rbourdil         ###   ########.fr       */
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
}
