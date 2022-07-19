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

int     is_builtin(t_shell *shell)
{
    if (ft_strcmp(shell->cmds[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(shell->cmds[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(shell->cmds[0], "env") == 0)
        return (1);
    else if (ft_strcmp(shell->cmds[0], "exit") == 0)
        return (1);
    else if (ft_strcmp(shell->cmds[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(shell->cmds[0], "export") == 0)
        return (1);
    else if(ft_strcmp(shell->cmds[0], "unset") == 0)
        return (1);
    return (0);
}

void    set_env_exp(t_shell *shell, char **env)
{
    char **arr;
	arr = sorted_exp(env);
    if (!arr)
        return ;   
    shell->env = init_env(env);
	shell->env_size = list_size(shell->env);
    shell->exp = init_env(arr);
	shell->exp_size = list_size(shell->exp);
    ft_free(arr);
}

void	env_exp_set(t_shell *shell)
{
	shell->env = init_env(shell->new_env);
	shell->exp = init_env(shell->new_exp);
}
/*
Function that calls the different built_ins
*/
// void    builtin_exec(t_shell *shell, char **environ, int loop_check)
// {
// 	if (loop_check == 0)
// 		set_env_exp(shell, environ);
// 	else if (loop_check > 0)
// 		env_exp_set(shell);
//     if (ft_strcmp(shell->cmds[0], "echo") == 0)
//     {
//         ft_echo(shell->cmds);
//         shell->new_env = list_to_array(shell->env);
// 		shell->new_exp = list_to_array(shell->exp);
//     }
//     else if (ft_strcmp(shell->cmds[0], "pwd") == 0)
//     {
//         ft_pwd();
//         shell->new_env = list_to_array(shell->env);
// 		shell->new_exp = list_to_array(shell->exp);
//     }
//     else if (ft_strcmp(shell->cmds[0], "env") == 0)
//     {
//         ft_env(shell->env);
//         shell->new_env = list_to_array(shell->env);
// 		shell->new_exp = list_to_array(shell->exp);
//     }
//     else if (ft_strcmp(shell->cmds[0], "exit") == 0)
//     {
//         shell->new_env = list_to_array(shell->env);
// 		shell->new_exp = list_to_array(shell->exp);
//         ft_exit(0, shell);
//     }
//     else if (ft_strcmp(shell->cmds[0], "cd") == 0)
//     {
//         ft_cd(shell->cmds);
//         shell->new_env = list_to_array(shell->env);
// 		shell->new_exp = list_to_array(shell->exp);
//     }
//     else if (ft_strcmp(shell->cmds[0], "export") == 0)
//     {
//         ft_export(shell);
// 		ft_print_list(shell->env);
//         shell->new_env = list_to_array(shell->env);
// 		print_env_array(shell->new_env);
// 		shell->new_exp = list_to_array(shell->exp);
//     }
//     else if(ft_strcmp(shell->cmds[0], "unset") == 0)
//     {
//         ft_unset(shell);
//         shell->new_env = list_to_array(shell->env);
// 		shell->new_exp = list_to_array(shell->exp);
//     }
//     ft_free_list(&shell->env);
//     ft_free_list(&shell->exp);
// }

void	dummy_builtin(t_shell *shell, char **environ, int loop_check)
{
	if (loop_check == 0)
    	set_env_exp(shell, environ);
	else if (loop_check > 0)
		env_exp_set(shell);
	if (ft_strcmp(shell->cmds[0], "export") == 0)
    {
        ft_export(shell);
		// ft_print_list(shell->env);
		printf("list size before function is %d\n", list_size(shell->env));
        shell->new_env = list_to_array(shell->env, 0);
		// print_env_array(shell->new_env);
		shell->new_exp = list_to_array(shell->exp, 1);
    }
	else
		printf("not the right built in\n");
}

int main(int ac, char **av, char **env)
{
    t_shell     shell;
    char        *str;
    extern char **environ;
	int			loop_check;

    str = NULL;
	loop_check = 0;
    if (ac == 1)
    {
        (void)av;
		print_env_array(env);
		printf("##########\n");
		print_env_array(environ);
		// shell.export = 0;
        // while (1)
        // {
        //     (void)av;
        //     str = ft_prompt(PROMPT_NAME); 
        //     if (str)
        //     {
        //         shell.cmds = cmd_split(str);
        //         free(str);
        //     }
        //     if (is_builtin(&shell) == 1)
        //     {
		// 		dummy_builtin(&shell, environ, loop_check);
        //         // builtin_exec(&shell, environ, loop_check);
        //         environ = shell.new_env;
        //     }
        //     else
        //         printf("%s\n", shell.cmds[0]);
		// 	// print_env_array(shell.new_exp);
		// 	// print_env_array(shell.new_env);
        //     if (shell.cmds)
        //         ft_free(shell.cmds);
		// 	loop_check++;
        // }
    }
    return (1);
}