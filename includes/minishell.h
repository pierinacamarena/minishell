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
#include <stddef.h>

#define PROMPT_NAME "minishell% "

typedef struct s_splitter {
	int		len;
	int		i;
	int		j;
	int		count;
}	t_splitter;

typedef struct s_env
{
	char			*content;
	char			*key;
}				t_env;

typedef struct s_env_list
{
	int					size;
	t_env				*node;
	struct s_env_list	*next;
}				t_env_list;

typedef struct	s_exp_list
{
	int					size;
	char				*content;
	struct s_exp_list	*next;
}				t_exp_list;

typedef struct s_shell
{
	char		**cmds;
	// char		**env_arr;
	t_env_list	*env;
	t_exp_list	*exp;
}				t_shell;

/*built_ins*/
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_env(t_env_list *env);
void    ft_exit(long long i, char **cmds);

/* utils */
int     ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(char const *str);
char	*ft_strdup(char const *str);
char	*ft_strchr(char const *str, int c);
char	*ft_substr(char const *str, unsigned int start, size_t len);
void	ft_bzero(void *str, size_t n);
void	*ft_memset(void *str, int character, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_free(char **str);
char	*ft_strjoin(char const *s1, char const *s2);

/*gnl*/
int     get_next_line(int fd, char **line);
char	*ft_eof(char *temp, char **line);
char	*ft_strnjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, char const *src, size_t size);

/*basic_parsing*/
void	single_quota(char *str, char **cmd, t_splitter *split);
void	double_quota(char *str, char **cmd, t_splitter *split);
void	space_case(char *str, char **cmd, t_splitter *split);
void	word_count(const char *str, int *i, int *count);
int     ft_count(const char *str);
int     ft_len(char const *s, char c, int i);
char	**cmd_malloc(char *str, char **cmd, t_splitter *split);
char	**cmd_split(const char *str);

/*ft_split*/
int			ft_wordcount(char const *s, char c);
char	**ft_split(char const *s, char c);

/*env*/
t_env_list	*init_env(char **env);
void		ft_add_node(t_env_list **begin, t_env_list *aux);
t_env_list	*ft_set_node(char *env);
void		ft_print_list(t_env_list *begin);

/*cd*/
int		ft_cd(char **cmds);

/*env_for_execute*/
char	**list_to_array(t_env_list *list);
void    print_env_array(char **env);

/*export_sort*/
size_t  array_size(char **arr);
void    ft_swap(char **a, char **b);
int     not_sorted(char **env);
void    print_double_array(char **str);
char    **sorted_exp(char **env);


/*export_list */
t_exp_list *ft_set_expo(char *env);
void    ft_add_expo(t_exp_list **begin, t_exp_list *aux);
t_exp_list	*init_exp(char **env);
void	ft_print_export(t_exp_list *begin);

/*sort_linked_list*/
void	bubble_sort(t_exp_list **first);
void	swap_export(t_exp_list *prev, t_exp_list *less, t_exp_list *more, t_exp_list **first);


/*export*/
void ft_export(t_shell *shell, char **env);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
#endif

#endif