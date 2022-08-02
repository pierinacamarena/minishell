#include "../includes/minishell.h"

char	*collect(t_buffer *buffer)
{
	flush(buffer);
	return (strdup(buffer->collector));
}

void	clear_buffer(t_buffer *buffer)
{
	buffer->pos = 0;
	free(buffer->collector);
	buffer->collector = NULL;
}

char	*collect_and_clear(t_buffer *buffer)
{
	char	*ret;

	ret = collect(buffer);
	clear_buffer(buffer);
	return (ret);
}
