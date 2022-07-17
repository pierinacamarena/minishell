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

// #include "../includes/minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>

char	*ft_strchr(char const *str, int c)
{
	while (*str != '\0' && *str != (char)c)
	{
		str++;
		if (*str == (char)c)
			return ((char *)str);
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

int main(int ac, char **av, char **env)
{  
    if (ac == 2)
    {
        if (ft_strchr(av[1], '='))
        {
            printf("invalid argument\n");
            return (0);
        }
        else
        {
            printf("good job\n");
            return (0);
        }
    }
    else
    {
        printf("wrong number of arguments");
        return (0);
    }
}
