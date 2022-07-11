/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 23:14:20 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 23:14:22 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int len_cmds(char **cmds)
{
    int len;
    while(cmds[len])
    {
        len++;
    }
    return (len);
}

int ft_cd(char **cmds)
{
    int len;

    if (!cmds)
        return (-1);
    len = len_cmds(cmds);
    if (len > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return (-1);
    }
    else if (len == 0)
    {
        printf("still not handled :] \n");
        return (1);
    }
    else if (len == 2)
    {
        
    }
}