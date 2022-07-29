#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1

typedef struct s_buffer {
	int		pos;
	char	buf[BUFSIZE];
	char	*collector;
}	t_buffer;

void	init_buffer(t_buffer *buffer);
int		add_char_to_buffer(t_buffer *buffer, int c);
int		add_str_to_buffer(t_buffer *buffer, char *str);
char	*collect(t_buffer *buffer);
void	clear_buffer(t_buffer *buffer);

#endif
