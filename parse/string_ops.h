#ifndef STRING_OPS_H
#define STRING_OPS_H

#include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_realloc(char *s, size_t size);
char	*append_str(char *s1, const char *s2);
char	*append_char(char *s1, const char c);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);

#endif
