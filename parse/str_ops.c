#include "str_ops.h"

char	*append_str(char *s1, const char *s2)
{
	s1 = realloc(s1, strlen(s1) + strlen(s2) + 1);
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
