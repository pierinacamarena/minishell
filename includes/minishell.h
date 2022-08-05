/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:12:55 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 21:25:51 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define PROMPT_NAME "minishell% "

/*	file type definitions */

#define READ_FILE 256
#define WRITE_FILE 257
#define HERE_DOC 258
#define APPEND_FILE 259
#define SIMPLE_WORD 260

/*	state definitions */

#define QUOTE_STATE 265
#define DOUBLE_QUOTE_STATE 266
#define WORD_STATE 267

/*  parsing defs */

#define BUFSIZE 1

/*	token type defs	*/

#define WORD_TOKEN 256
#define MORE_TOKEN 257
#define MORE_MORE_TOKEN 258
#define LESS_TOKEN 259
#define LESS_LESS_TOKEN 260
#define PIPE_TOKEN 261
#define OR_TOKEN 262
#define AND_TOKEN 263
#define EOF_TOKEN 264

/*	state definitions */

#define QUOTE_STATE 265
#define DOUBLE_QUOTE_STATE 266
#define WORD_STATE 267

#define PANIC_MODE 1
#define REGULAR_MODE 0

/*	error defs	*/

#define ENV 0x1
#define CMD 0x2
#define HIST 0x4

/*	global exit status variable	*/

extern int	g_exit_code;

typedef struct	s_scanner {
	const char	*start;
	const char	*current;
}	t_scanner;

typedef struct s_token {
	int			type;
	const char	*start;
	int			length;
}	t_token;

typedef struct s_parse {
	t_token		*current;
	t_scanner	*scanner;
	int			*panic;
}	t_parse;

typedef struct s_elem {
	char			*words;
	int				type;
	struct s_elem	*next;
}	t_elem;

typedef struct s_pipeline {
	char				**command;
	t_elem				*redirections;
	struct s_pipeline	*next;
}	t_pipeline;

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
	t_env				*node;
	struct s_env_list	*next;
}				t_env_list;

typedef struct	s_exp_list
{
	char				*content;
	struct s_exp_list	*next;
}				t_exp_list;

typedef struct s_buffer {
	int		pos;
	char	buf[BUFSIZE];
	char	*collector;
}	t_buffer;

typedef struct	s_pipes
{
	int **fd_pipe;
	int	size;
}				t_pipes;
typedef struct s_shell
{
	char		**env_exec;
	t_env_list	*env;
	t_env_list	*exp;
}				t_shell;

/*minishell*/
int   	builtin_exec_list(t_pipeline *data, t_shell *shell, int *read_write_fds);
int     is_builtin_list(t_pipeline *shell);
int		get_heredoc(char *heredoc);
int		do_redir(t_elem *redirections);
void	get_redirs(t_elem *redirections, int *read_write_fds);

/*builtins_list*/
//int		ft_pwd(void);
int		len_cmds_list(char **cmds);
int		ft_pwd(int *read_write_fds);
int		ft_env(t_env_list *env, int *read_write_fds);
int		ft_exit_list(t_shell *shell, t_pipeline *data);
int	    ft_unset_list(t_shell *shell, t_pipeline *data);
int	    ft_export_list(t_shell *shell, t_pipeline *data, int *read_write_fds);
int		ft_cd_list(t_shell *shell, t_pipeline *data);

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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void    ft_putchar_fd(char c, int fd);
void    ft_putstr_fd(char *s, int fd);
void    ft_putendl_fd(char *s, int fd);
char	*ft_itoa(int n);
void	full_free(t_shell *shell, t_pipeline *data);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_isalnum(int c);

/* errors */
void	free_struct(t_shell *shell, t_pipeline *cmds, int opt);
void	write_error(char *str);
void	free_exit(int exit_status, t_shell *shell, t_pipeline *cmds, int opt);
void	print_exit(int exit_status, char *msg);

/*ft_split*/
int			ft_wordcount(char const *s, char c);
char	**ft_split(char const *s, char c);

/*env_setup*/
t_env_list	*init_env(char **env);
void		ft_add_node(t_env_list **begin, t_env_list *aux);
t_env_list	*ft_set_node(char *env);
void		ft_print_list(t_env_list *begin);
void		ft_free_list(t_env_list **begin);

/*env_for_execute*/
char	**list_to_array(t_env_list *list);
void    print_env_array(char **env);

/*export_sort*/
size_t  array_size(char **arr);
void    ft_swap(char **a, char **b);
int     not_sorted(char **env);
void    print_double_array(char **str);
char    **sorted_exp(char **env);

/*list_utils */
void    find_replace(t_env_list **list, char *key, char *new_content);
int		list_size(t_env_list *list);
int     key_exists(t_env_list *list, char *var);
int     same_value(t_env_list *list, char *var);
char    *ft_getenv(t_env_list *begin, char *key);
char	*ft_str3join(char const *s1, char const *s2, char const *s3);

/*echo*/
//int		ft_echo(char **args);
int		ft_echo(char **args, int *read_write_fds);

/*ft_path*/
char	*ft_path(char *arg, char **env);
char	*cmd_tester(char **path_split, char *arg);

/*signal*/
void	sighandler(int signum);
void	siginit(int signum, void (*sighandler)(int));

/*execute_list*/
int	exec_pipes(t_pipeline *data, t_shell *shell);

/*PARSING FUNCTIONS ! :D*/

/*buffer.h*/

void	init_buffer(t_buffer *buffer);
int		flush(t_buffer *buffer);
int		add_char_to_buffer(t_buffer *buffer, int c);
int		add_str_to_buffer(t_buffer *buffer, char *str);
char	*collect(t_buffer *buffer);
void	clear_buffer(t_buffer *buffer);
char	*collect_and_clear(t_buffer *buffer);

/*expand.h*/

char	*expand_parameters(t_token token, t_shell *shell);
t_elem	*split_words(t_elem *elem);

/*lexer.h*/

t_token	scan_token(t_scanner *scanner);

/*list.h*/

t_elem	*add_elem_to_list(t_elem *head, t_elem *new_elem);
t_elem	*copy_elem(t_elem *src);
void	print_elem_list(t_elem *head);
void	print_commands_list(t_pipeline *commands_list);
void	free_elem(t_elem *elem);
void	free_elem_list(t_elem *elem);
void	free_commands_list(t_pipeline *pipeline);

/*parser.h*/

int	parse(t_scanner *scanner, t_shell *shell);

/*scanner.h*/

void	init_scanner(t_scanner *scanner, const char *line);
int		advance(t_scanner *scanner);
int		peek(t_scanner scanner);
void	skip_blanks(t_scanner *scanner);

/*semantics.h*/

t_elem		*new_words_list(t_elem *words_list, t_elem *elem);
t_elem		*new_elem(t_elem *elem_list, t_token token, int type, t_shell *shell);
t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list);

/*string_ops.h*/

char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strndup(const char *s, size_t n);
char	*ft_realloc(char *s, size_t size);
char	*append_str(char *s1, const char *s2);
char	*append_char(char *s1, const char c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);

/*utils.h*/

int		ft_isblank(int c);
int		ft_ismeta(int c);
int		update_state(int state, int c);
void	free_double_ptr(char **ptr);

#endif
