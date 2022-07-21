#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/*	file type definitions */

#define READ_FILE 256
#define WRITE_FILE 257
#define HERE_DOC 258
#define APPEND_FILE 259
#define SIMPLE_WORD 260

/*	size of the buffer in expand_parameters */

#define BUFSIZE 4096

/*	token type definitions */

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

#endif
