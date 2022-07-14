#include "parse.h"

int	ft_ismeta(int c)
{
	//remove & condition and find an alternative
	if (c == '&' || c == '<' || c == '>' || c == '|' || c == '\n')
		return (1);
	return (0);
}

char	*ft_append(char *s1, char *s2)
{
	char	*ret;
	char	*p;

	if (s1 == NULL)
		ret = (char *)malloc(sizeof(char) * (strlen(s2) + 1));
	else
		ret = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	p = ret;
	while (s1 != NULL && *s1 != '\0')
		*p++ = *s1++;
	while (*s2 != '\0')
		*p++ = *s2++;
	*p = '\0';
	return (ret);
}

static char	*getop(char *pos, char **lexeme)
{
	char	buf[3];
	int		i;

	i = 0;
	buf[i++] = *pos++;
	if (buf[0] == *pos)
		buf[i++] = *pos++;
	buf[i] = '\0';
	*lexeme = strdup(buf);
	return (pos);
}

static char	*getword(char *pos, char **lexeme)
{
	char	*tmp;

	*lexeme = strnjoin("", pos++, 1);
	while (*pos != '\0' && !ft_ismeta(*pos) && !isblank(*pos))
	{
		tmp = *lexeme;		
		*lexeme = strnjoin(tmp, pos++, 1);
		free(tmp);
	}
	return (pos);
}

t_token	*get_token(t_token *symtable[], char *line)
{
	t_token		*token;
	static char	*pos;
	int			tag;
	char		*lexeme;
	char		*tmp;
	
	if (line != NULL)
		pos = line;
	if (*pos == '\0')
		return (NULL);
	while (isblank(*pos))
		pos++;
	if (*pos == '\0')
		return (NULL);
	else if (ft_ismeta(*pos))
	{
		tag = OPERATOR;
		pos = getop(pos, &lexeme);
	}
	else
	{
		tag = WORD;
		pos = getword(pos, &lexeme);
	}
	token = install(symtable, tag, lexeme);
	free(lexeme);
	return (token);
}
