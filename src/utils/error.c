#include "minishell.h" 

void	free_struct(t_shell *shell, t_pipeline *cmds, int opt)
{
	if ((opt & ENV) != 0)
	{
		ft_free_list(&shell->env);
		ft_free_list(&shell->exp);
	}
	if ((opt & CMD) != 0)
		free_commands_list(cmds);
}

void	write_error(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
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
