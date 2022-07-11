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

char *ft_prompt(char const *str)
{
    char    *prompt;

    prompt = readline(str);
    return (prompt);
}

int check_builtin(t_shell *shell, char **env)
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
        ft_env(env);
        return (1);
    }
    else if (ft_strcmp(shell->cmds[0], "exit") == 0)
    {
        ft_exit(0, shell->cmds);
    }
    else if (ft_strcmp(shell->cmds[0], "cd") == 0)
    {
        ft_cd(shell->cmds);
        return (1);
    }
    return (0);
}

int main(int ac, char **av, char **env)
{
    t_shell shell;
    char    *str;
    int     built_in;

    str = NULL;
    
    if (ac == 1)
    {    
        while (1)
        {
            (void)av;
            str = ft_prompt(PROMPT_NAME); 
            if (str)
            {
                shell.cmds = cmd_split(str);
                free(str);
            }
            built_in = check_builtin(&shell, env);
            if (built_in == 0)
                printf("%s\n", str);
            if (shell.cmds)
                ft_free(shell.cmds);
        }
    
    }
    return (1);
}