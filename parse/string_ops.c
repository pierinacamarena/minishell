#include "string_ops.h"

size_t	ft_strlen(const char *s)
{
	const char	*end;

	end = s;
	while (*end != '\0')
		end++;
	return (end - s);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
		dest[i++] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*ret;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (ret == NULL)
		return (NULL);
	ft_strcpy(ret, s);
	return (ret);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc(sizeof(char) * (n + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
