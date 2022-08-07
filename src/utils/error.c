/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:06:17 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/07 14:19:19 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

void	free_struct(t_shell *shell, t_pipeline *cmds, int opt)
{
	if ((opt & ENV) != 0)
	{
		ft_free_list(&shell->env);
		ft_free_list(&shell->exp);
		free(shell->prompt);
	}
	if ((opt & CMD) != 0)
		free_commands_list(cmds);
}

void	write_error(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	free_exit(int exit_status, t_shell *shell, t_pipeline *cmds, int opt)
{
	free_struct(shell, cmds, opt);
	if ((opt & HIST) != 0)
		rl_clear_history();
	exit(exit_status);
}

void	print_exit(int exit_status, char *msg)
{
	write_error(msg);
	exit(exit_status);
}
