/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:24:43 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 18:24:45 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
