#ifndef TAC_TOKEN_H
#define TAC_TOKEN_H

typedef struct TOKEN_STRUCT
{
	char*	value;
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_COLON,
		TOKEN_COMMA,
		TOKEN_LT,
		TOKEN_GT,
		TOKEN_ARROW_RIGHT,
		TOKEN_INT,
		TOKEN_SEMI,
		TOKEN_EOF
		// TOKEN_FLAGS, // - Flags of command
		// TOKEN_PIPE, // | pipe
		// TOKEN_HIOME_DIR, // Home directory
		// TOKEN_V_EXPRESSION, // ? Variable expression
		// TOKEN_SQ, // ' single qoute
		// TOKEN_DQ, // " double qoute
		// TOKEN_LT, // < inpute redirection
		// TOKEN_GT, // > output redirection
		// TOKEN_APPAND, // >> appandade output redirection
		// TOKEN_HERDOC, // << her_doc
		// TOKEN_EOF, // end of file
	} type;
} token_T;

token_T* init_token(char* value, int type);
const char* token_type_to_str(int type);
char* token_to_str(token_T* token);

#endif