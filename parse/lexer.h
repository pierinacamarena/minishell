#ifndef LEXER_H
#define LEXER_H

#include "scanner.h"
#include "utils.h"

/*	token type defs	*/

#define WORD_TOKEN 256
#define MORE_TOKEN 257
#define MORE_MORE_TOKEN 258
#define LESS_TOKEN 259
#define LESS_LESS_TOKEN 260
#define PIPE_TOKEN 261
#define OR_TOKEN 262
#define AND_TOKEN 263
#define EOF_TOKEN 264

/*	state definitions */

#define QUOTE_STATE 265
#define DOUBLE_QUOTE_STATE 266
#define WORD_STATE 267

/*	struct defs		*/

typedef struct s_token {
	int			type;
	const char	*start;
	int			length;
}	t_token;

/*	function declarations	*/

t_token	scan_token(t_scanner *scanner);

#endif
