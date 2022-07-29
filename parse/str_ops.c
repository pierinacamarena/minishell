#include "str_ops.h"

char	*append_str(char *s1, const char *s2)
{
	int	size1;
	int	size2;

	if (s1 == NULL)
		size1 = 0;
	else
		size1 = strlen(s1);
	size2 = strlen(s2);
	s1 = realloc(s1, size1 + size2 + 1);
	if (s1 == NULL)
		return (NULL);
	strcat(s1, s2);
	return (s1);
}

char	*append_char(char *s1, const char c)
{
	s1 = realloc(s1, strlen(s1) + 2);
	if (s1 == NULL)
		return (NULL);
	strncat(s1, &c, 1);
	return (s1);
}
