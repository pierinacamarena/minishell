/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:46:18 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/05 22:11:31 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	unsigned char		c1;
	unsigned char		c2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	c1 = *p1;
	c2 = *p2;
	while (c1 == c2)
	{
		c1 = (unsigned char)*p1++;
		c2 = (unsigned char)*p2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char const *str)
{
	char	*strdup;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	strdup = (char *)malloc(sizeof(char) * len + 1);
	if (!strdup)
		return (NULL);
	while (str[++i])
		strdup[i] = str[i];
	strdup[i] = '\0';
	return (strdup);
}

char	*ft_strchr(char const *str, int c)
{
	while (*str != '\0' && *str != (char)c)
	{
		str++;
		if (*str == (char)c)
			return ((char *)str);
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	while (str[start + i] && len--)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*copy;

	copy = (void *)malloc(size * count);
	if (!copy)
		return (NULL);
	ft_bzero(copy, size * count);
	return (copy);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}

void	*ft_memset(void *str, int character, size_t n)
{
	char			*str2;
	unsigned char	character2;

	str2 = (char *)str;
	character2 = (unsigned char)character;
	while (n--)
		*str2++ = character2;
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		i;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((size + 1) * sizeof(*str));
	i = -1;
	while (*s1)
		str[++i] = *s1++;
	while (*s2)
		str[++i] = *s2++;
	str[++i] = 0;
	return (str);
}

char	*ft_str3join(char const *s1, char const *s2, char const *s3)
{
	int		size;
	int		i;
	char	*str;

	if (s1 == 0 || s2 == 0 || s3 == 0)
		return (0);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = (char *)malloc((size + 1) * sizeof(*str));
	i = -1;
	while (*s1)
		str[++i] = *s1++;
	while (*s2)
		str[++i] = *s2++;
	while (*s3)
		str[++i] = *s3++;
	str[++i] = 0;
	return (str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

static int	size_int(int n)
{
	int	size;

	size = 1;
	while (n > 9 || n < -9)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	int		neg;
	char	*nb_arr;

	neg = 0;
	if (n < 0)
		neg = 1;
	size = size_int(n) + neg;
	nb_arr = malloc(sizeof(char) * (size + 1));
	if (!nb_arr)
		return (0);
	if (neg)
		nb_arr[0] = '-';
	nb_arr[size] = '\0';
	while (size > neg)
	{
		nb_arr[size - 1] = (n % 10) * (1 - (2 * neg)) + '0';
		n /= 10;
		size--;
	}
	return (nb_arr);
}

void	full_free(t_shell *shell, t_pipeline *data)
{
	if (shell->env_exec)
		ft_free(shell->env_exec);
	ft_free_list(&shell->env);
	ft_free_list(&shell->exp);
	free_commands_list(data);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		nb = (nb * 10) + ((*str++) - '0');
	return (nb * sign);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}