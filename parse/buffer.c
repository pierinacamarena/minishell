#include "../includes/minishell.h"

void	init_buffer(t_buffer *buffer)
{
	buffer->pos = 0;
	buffer->collector = NULL;
}

int	flush(t_buffer *buffer)
{
	int	collector_size;

	if (buffer->collector != NULL)
		collector_size = strlen(buffer->collector);
	else
		collector_size = 0;
	buffer->collector = realloc(buffer->collector, \
collector_size + buffer->pos + 1);
	buffer->collector[collector_size] = '\0';
	if (buffer->collector == NULL)
		return (-1);
	strncat(buffer->collector, buffer->buf, buffer->pos);
	buffer->pos = 0;	
	return (0);
}
	
int	add_char_to_buffer(t_buffer *buffer, int c)
{
	int	status;

	status = 0;
	if (buffer->pos >= BUFSIZE)
		status = flush(buffer);
	if (status == -1)
		return (-1);
	buffer->buf[buffer->pos++] = c;
	return (0);
}

int	add_str_to_buffer(t_buffer *buffer, char *str)
{
	int	status;

	while (*str != '\0')
	{
		status = add_char_to_buffer(buffer, *str++);
		if (status == -1)
			return (-1);
	}
	return (0);
}
