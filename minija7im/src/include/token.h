#ifndef TAC_TOCEN_H
#define TAC_TOKEN_H

typedef struct TOKEN_STRUCT
{
	char*	value;
	enum
	{
		TOKEN_ID,
		TOKEN_HIOME_DIR, // Home directory
		TOKEN_V_EXPRESSION, // ? Variable expression
		// TOKEN_
		TOKEN_SQ, // ' single qoute
		TOKEN_DQ, // " double qoute
		TOKEN_LT, // < inpute redirection
		TOKEN_GT, // > output redirection
		TOKEN_PIPE, // | pipe
		TOKEN_EOF, // end of file
	} type;
} token_T;

token_T*	init_token(char* value, int type);

#endif