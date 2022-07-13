#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

size_t  array_size(char **arr)
{
    int len;

    len = 0;
    while (arr[len])
        len++;
    return (len);
}

void    ft_swap(char **a, char **b)
{
    char *temp;

    temp = *a;
    *a = *b;
    *b = temp;
    // free(temp);
}

int     not_sorted(char **env)
{
    int comp;
    int i;
    int size;

    i = 0;
    size = array_size(env);
    while (env[i] && env[i+1])
    {
        if (ft_strcmp(env[i], env[i+1]) > 0)
            return (1);
        i++;
    }
    if (ft_strcmp(env[size - 2], env[size - 1]) > 0)
    {
        printf("%s\n%s\n", env[size-2], env[size - 1]);
        return (1);
    }
    return (0);
}

void    ft_print_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}

int main (int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    int     sort;
    int     i;
    int     size;
    char    **arr;

    i = 0;
    size = array_size(env);
    arr = (char **)malloc(sizeof(char *) * 10 + 1);
    if (!arr)
        return (-1);
    // printf("here\n");
    while(i < 10)
    {
        // printf("moew\n");
        arr[i] = ft_strdup(env[i]);
        i++;
    }
    arr[i] = NULL;
    size = array_size(arr);
    ft_print_env(arr);
    {
        while (arr[i] && arr[i + 1] && i < 10)
        {
            if (ft_strcmp(arr[i], arr[i + 1]) > 0)
            {
                printf("i is %d\n",i);
                ft_swap(&arr[i], &arr[i + 1]);
            }
            i++;
        }
        if (ft_strcmp(arr[size - 2], arr[size - 1]))
            ft_swap(&arr[size - 2], &arr[size - 1]);
    }
    ft_print_env(env);
    return (0);
}