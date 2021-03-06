#include "../includes/minishell.h"

char	*ft_realloc(char *s, size_t size)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * size);
	if (ret == NULL)
	{
		free(s);
		return (NULL);
	}
	ft_strncpy(ret, s, size);
	free(s);
	return (ret);
}

char	*append_str(char *s1, const char *s2)
{
	int	size1;
	int	size2;

	if (s1 == NULL)
		size1 = 0;
	else
		size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	s1 = ft_realloc(s1, size1 + size2 + 1);
	if (s1 == NULL)
		return (NULL);
	ft_strcat(s1, s2);
	return (s1);
}

char	*append_char(char *s1, const char c)
{
	s1 = ft_realloc(s1, ft_strlen(s1) + 2);
	if (s1 == NULL)
		return (NULL);
	ft_strncat(s1, &c, 1);
	return (s1);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
