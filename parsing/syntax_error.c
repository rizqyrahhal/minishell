/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:59:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 13:42:03 by rarahhal         ###   ########.fr       */
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

int	one(t_token *token, t_token *next_token)
{
	if (token->e_type == TOKEN_PIPE && !next_token)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	if (token->e_type == TOKEN_PIPE && (next_token->e_type == TOKEN_PIPE
			|| !next_token->value))
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (0);
}

int	too(t_token *token, t_token *next_token)
{
	if ((token->e_type == TOKEN_HERDOC || token->e_type == TOKEN_IN
			|| token->e_type == TOKEN_OU || token->e_type == TOKEN_APPAND
			|| token->e_type == TOKEN_PIPE) && (!next_token->value))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if ((token->e_type == TOKEN_HERDOC || token->e_type == TOKEN_IN
			|| token->e_type == TOKEN_OU || token->e_type == TOKEN_APPAND)
		&& (next_token->e_type == TOKEN_HERDOC || next_token->e_type == TOKEN_IN
			|| next_token->e_type == TOKEN_OU
			|| next_token->e_type == TOKEN_APPAND
			|| next_token->e_type == TOKEN_PIPE))
	{	
		printf("minishell: syntax error near unexpected token `%s'\n",
			next_token->value);
		return (-1);
	}
	return (0);
}

int	syntax_logic(t_lexer **l, t_lexer **nl, t_token **t, t_token **nt)
{
	while ((*t)->e_type != TOKEN_EOF)
	{
		lexer_skip_whitespace(*nl);
		free((*nt)->value);
		free(*nt);
		*nt = lexer_next_token(*nl);
		if (one(*t, *nt) == -1 || too(*t, *nt) == -1)
			return (-1);
		free((*t)->value);
		free(*t);
		*t = lexer_next_token(*l);
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
	if (one(token, next_token) == -1)
	{
		*i = lexer->i;
		ft_free_(lexer, next_lexer, token, next_token);
		return (-1);
	}
	if (syntax_logic(&lexer, &next_lexer, &token, &next_token) == -1)
	{
		*i = lexer->i;
		ft_free_(lexer, next_lexer, token, next_token);
		return (-1);
	}
	ft_free_(lexer, next_lexer, token, next_token);
	if (unclosed_quotes(src, &i) == -1)
		return (-1);
	return (0);
}
