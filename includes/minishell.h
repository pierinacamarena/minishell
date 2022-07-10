/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:43:12 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 18:43:15 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT_NAME "minishell% "

/*built_ins*/
int ft_echo(char **args);
int ft_pwd(void);
int ft_env(char **env);
void    ft_exit(long long i, char *str);

/* utils */
int     ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(char const *str);
char	*ft_strdup(char const *str);
char	*ft_strchr(char const *str, int c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	ft_strdel(char **str);

/*gnl*/
int     get_next_line(int fd, char **line);
char	*ft_eof(char *temp, char **line);
char	*ft_strnjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char const *src, size_t size);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
#endif

#endif