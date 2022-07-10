/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:16:36 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/10 17:16:51 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcpy(char *dst, char const *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strnjoin(char *s1, char *s2)
{
	char	*joinedstr;
	size_t	ls1;
	size_t	ls2;
	size_t	ljoined;

	ls1 = 0;
	if (s1)
		ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	ljoined = ls1 + ls2;
	joinedstr = (char *)malloc(sizeof(char) * ljoined + 1);
	if (!joinedstr)
		return (NULL);
	if (s1)
	{
		ft_strlcpy(joinedstr, s1, (ls1 + 1));
		free(s1);
	}
	ft_strlcpy(joinedstr + ls1, s2, (ls2 + 1));
	return (joinedstr);
}

static bool	ft_is_line_process(char **temp, char **line)
{
	char	*found;
	size_t	end;
	size_t	len;

	len = 0;
	found = NULL;
	found = ft_strchr(*temp, '\n');
	if (found)
	{
		end = found - *temp;
		len = ft_strlen(found);
		*line = ft_substr(*temp, 0, end);
		ft_strlcpy(*temp, (found + 1), (len + 1));
		return (true);
	}
	return (false);
}

char	*ft_eof(char *temp, char **line)
{
	if (temp && *temp)
		*line = ft_strdup(temp);
	else
		*line = ft_strdup("");
	return (*line);
}

int	get_next_line(int fd, char **line)
{
	int				ret;
	char			buffer[BUFFER_SIZE + 1];
	static char		*temp;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	if (temp && ft_is_line_process(&temp, line))
		return (1);
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		temp = ft_strnjoin (temp, buffer);
		if (!temp)
			return (-1);
		if (ft_is_line_process(&temp, line))
			return (1);
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	if (ret < 0)
		return (-1);
	*line = ft_eof(temp, line);
	free(temp);
	temp = NULL;
	return (0);
}
