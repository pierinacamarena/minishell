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
/*
Function that calls the different built_ins
*/

char  **check_builtin(t_shell *shell, int *result, char **environ)
{
    char **env_array;

    set_env_exp(shell, environ);
    if (ft_strcmp(shell->cmds[0], "echo") == 0)
    {
        ft_echo(shell->cmds);
        *result = 1;
        env_array = list_to_array(shell->env);
    }
    else if (ft_strcmp(shell->cmds[0], "pwd") == 0)
    {
        ft_pwd();
        *result = 1;
        env_array = list_to_array(shell->env);
    }
    else if (ft_strcmp(shell->cmds[0], "env") == 0)
    {
        ft_env(shell->env);
        *result = 1;
        env_array = list_to_array(shell->env);
    }
    else if (ft_strcmp(shell->cmds[0], "exit") == 0)
    {
        ft_exit(0, shell);
        env_array = list_to_array(shell->env);
    }
    else if (ft_strcmp(shell->cmds[0], "cd") == 0)
    {
        ft_cd(shell->cmds);
        *result = 1;
        env_array = list_to_array(shell->env);
    }
    else if (ft_strcmp(shell->cmds[0], "export") == 0)
    {
        ft_export(shell);
        *result = 1;
        env_array = list_to_array(shell->env);
    }
    else if(ft_strcmp(shell->cmds[0], "unset") == 0)
    {
        ft_unset(shell);
        *result = 1;
        env_array = list_to_array(shell->env);
    }
    ft_free_list(&shell->env);
    ft_free_list(&shell->exp);
    return (env_array);
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

int main(int ac, char **av)
{
    t_shell     shell;
    char        *str;
    int         built_in;
    extern char **environ;
    char        **new_env;

    str = NULL;
    built_in = 0;
    if (ac == 1)
    {
        if (!environ)
            return (2);
        
        (void)av;
        while (1)
        {
            (void)av;
            str = ft_prompt(PROMPT_NAME); 
            if (str)
            {
                shell.cmds = cmd_split(str);
                free(str);
            }
            if (is_builtin(&shell) == 1)
            {
                new_env = check_builtin(&shell, &built_in, environ);
                environ = new_env;
            }
            else
                printf("%s\n", shell.cmds[0]);
            if (shell.cmds)
                ft_free(shell.cmds);
        }
    }
    return (1);
}