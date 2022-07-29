#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/*	file type definitions */

#define READ_FILE 256
#define WRITE_FILE 257
#define HERE_DOC 258
#define APPEND_FILE 259
#define SIMPLE_WORD 260

/*	state definitions */

#define QUOTE_STATE 265
#define DOUBLE_QUOTE_STATE 266
#define WORD_STATE 267

/*	errors */

#define	TOKEN_ERROR 256

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
