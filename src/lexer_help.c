/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:47:21 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/30 15:50:00 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

// return lexer->src[i + 1] if exist or '\0'
char	lexer_peek(t_lexer *lexer, int offset)
{
	return (lexer->src[get_min(lexer->i + offset, lexer->src_size)]);
}

t_token	*lexer_advance_with(t_lexer *lexer, t_token *token)
{
	lexer_advance(lexer);
	return (token);
}

t_token	*help1_next_token(t_lexer *lexer)
{
	if (lexer_peek(lexer, 1) == '<')
	{
		lexer->i += 1;
		return (lexer_advance_with(lexer,
				init_token(ft_strdup("<<"), TOKEN_HERDOC)));
	}
	else
		return (lexer_advance_with(lexer,
				init_token(ft_strdup("<"), TOKEN_IN)));
}

t_token	*help2_next_token(t_lexer *lexer)
{
	if (lexer_peek(lexer, 1) == '>')
	{
		lexer->i += 1;
		return (lexer_advance_with(lexer,
				init_token(ft_strdup(">>"), TOKEN_APPAND)));
	}
	else
		return (lexer_advance_with(lexer,
				init_token(ft_strdup(">"), TOKEN_OU)));
}
