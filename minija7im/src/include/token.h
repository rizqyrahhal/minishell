#ifndef TAC_TOCEN_H
#define TAC_TOKEN_H

typedef struct TOKEN_STRUCT
{
	char*	value;
	enum
	{
		TOKEN_ID,
		TOKEN_LT,
		TOKEN_GT,
		TOKEN_PIPE,
		TOKEN_EOF,
	} type;
} token_T;

token_T*	init_token(char* value, int type);

#endif