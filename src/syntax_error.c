/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:59:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/27 14:03:00 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init(t_lexer **lexer, t_lexer **next_lexer, char **src)
{
	*lexer = init_lexer(*src);
	*next_lexer = init_lexer(*src);
	(*lexer)->not_expand = -1;
	(*next_lexer)->not_expand = -1;
}

int	one(t_token *token, t_token *next_token, t_lexer *lexer, int **i)
{
	if (token->e_type == TOKEN_PIPE && !next_token)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		**i = lexer->i;
		return (-1);
	}
	if (token->e_type == TOKEN_PIPE && (next_token->e_type == TOKEN_PIPE
			|| !next_token->value))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		**i = lexer->i;
		return (-1);
	}
	return (0);
}

int	too(t_token *token, t_token *next_token, t_lexer *lexer, int **i)
{
	if ((token->e_type == TOKEN_HERDOC || token->e_type == TOKEN_IN
			|| token->e_type == TOKEN_OU || token->e_type == TOKEN_APPAND
			|| token->e_type == TOKEN_PIPE) && (!next_token->value))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		**i = lexer->i;
		return (-1);
	}
	if ((token->e_type == TOKEN_HERDOC || token->e_type == TOKEN_IN
			|| token->e_type == TOKEN_OU || token->e_type == TOKEN_APPAND)
		&& (next_token->e_type == TOKEN_HERDOC || next_token->e_type == TOKEN_IN
			|| next_token->e_type == TOKEN_OU || next_token->e_type == TOKEN_APPAND
			|| next_token->e_type == TOKEN_PIPE))
	{	
		printf("minishell: syntax error near unexpected token `%s'\n",
			next_token->value);
		**i = lexer->i;
		return (-1);
	}
	return (0);
}

int	check_syntax_error(char *src, int *i)
{
	t_lexer	*lexer;
	t_lexer	*next_lexer;
	t_token	*token;
	t_token	*next_token;

	init(&lexer, &next_lexer, &src);
	token = lexer_next_token(lexer);
	next_token = lexer_next_token(next_lexer);
	if (one(token, next_token, lexer, &i) == -1)
		return (-1);
	while (token->e_type != TOKEN_EOF)
	{
		if (next_lexer->c == ' ')
			lexer_skip_whitespace(next_lexer);
		next_token = lexer_next_token(next_lexer);
		if (one(token, next_token, lexer, &i) == -1)
			return (-1);
		if (too(token, next_token, lexer, &i) == -1)
			return (-1);
		token = lexer_next_token(lexer);
	}
	if (unclosed_quotes(src, &i) == -1)
		return (-1);
	return (0);
}