/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:54:51 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/27 17:54:53 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sighandler(int signum)
{
	char		*env;

	write(1, "\b\b  \n", 5);
	env = getcwd(NULL, 0);
	printf("minishell%% ");
	free(env);
	env = NULL;
	(void)signum;
}
