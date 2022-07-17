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

/*
Function that calls the different built_ins
*/

int check_builtin(t_shell *shell)
{
    if (ft_strcmp(shell->cmds[0], "echo") == 0)
    {
        ft_echo(shell->cmds);
        return (1);
    }
    else if (ft_strcmp(shell->cmds[0], "pwd") == 0)
    {
        ft_pwd();
        return (1);
    }
    else if (ft_strcmp(shell->cmds[0], "env") == 0)
    {
        ft_env(shell->env);
        return (1);
    }
    else if (ft_strcmp(shell->cmds[0], "exit") == 0)
    {
        ft_exit(0, shell);
    }
    else if (ft_strcmp(shell->cmds[0], "cd") == 0)
    {
        ft_cd(shell->cmds);
        return (1);
    }
    else if (ft_strcmp(shell->cmds[0], "export") == 0)
    {
        ft_export(shell);
        return (1);
    }
    else if(ft_strcmp(shell->cmds[0], "unset") == 0)
    {
        ft_unset(shell);
        return (1);
    }
    return (0);
}

void    set_env_exp(t_shell *shell, char **env)
{
    char **arr;

    arr = sorted_exp(env);
    if (!arr)
        return ;   
    shell->env = init_env(env);
    shell->exp = init_env(arr);
    ft_free(arr);
}

int main(int ac, char **av, char **env)
{
    t_shell shell;
    char    *str;
    int     built_in;


    str = NULL;
    if (ac == 1)
    {
        if (!env)
            return (2);
        set_env_exp(&shell, env);
        while (1)
        {
            (void)av;
            str = ft_prompt(PROMPT_NAME); 
            if (str)
            {
                shell.cmds = cmd_split(str);
                free(str);
            }
            built_in = check_builtin(&shell);
            if (built_in == 0)
                printf("%s\n", shell.cmds[0]);
            if (shell.cmds)
                ft_free(shell.cmds);
        }
    }
    return (1);
}