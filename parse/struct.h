#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_scanner {
	const char	*start;
	const char	*current;
}	t_scanner;

typedef struct s_token {
	int				type;
	const char		*start;
	int				length;
}	t_token;

typedef struct s_elem {
	char			*words;
	int				type;
	struct s_elem	*next;
}	t_elem;

typedef struct s_pipeline {
	t_elem				*command;
	struct s_pipeline	*next;
}	t_pipeline;

#endif
