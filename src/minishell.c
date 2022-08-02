/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:52:54 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 03:11:09 by pcamaren         ###   ########.fr       */
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
	shell->cmds = 0;
	shell->env_exec = 0;
    ft_free(arr);
}

int main(int ac, char **av, char **env)
{
    t_shell     shell;
	t_list		*cmd_parse;
    char        *str;
	int			i;

    str = NULL;
	cmd_parse = NULL;
    if (ac == 1)
    {
        (void)av;
        set_env_exp(&shell, env);
        while (1)
        {
            (void)av;
			shell.cmds = 0;
			signal(SIGINT, sighandler);
            str = ft_prompt(PROMPT_NAME); 
            if (str && *str)
            {
                shell.cmds = cmd_split(str);
                free(str);
            }
			i = 0;
			if (shell.cmds)
			{
				while(shell.cmds[i])
				{
					parse_arg(&cmd_parse, shell.cmds[i]);
					i++;
				}
			}
			list_rewind(&cmd_parse);
			set_redir(cmd_parse);
			// print_parse_list(cmd_parse);
			if (shell.cmds)
				exec_list(&cmd_parse, &shell);
			list_clear(&cmd_parse);
            if (shell.cmds)
				ft_free(shell.cmds);
        }
    }
    return (1);
}