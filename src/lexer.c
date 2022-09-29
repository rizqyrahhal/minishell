/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:00 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/29 17:51:31 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	*init_lexer(char *src)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->src = src;
	lexer->src_size = ft_strlen(src);
	lexer->i = 0;
	lexer->c = src[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == 13 || lexer->c == 10
		|| lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

t_token	*lexer_advance_current(t_lexer *lexer, int type)
{
	char	*value;
	t_token	*token;

	value = malloc(2);
	value[0] = lexer->c;
	value[1] = '\0';
	token = init_token(value, type);
	lexer_advance(lexer);
	return (token);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	while (lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);
		if (ft_non_tokenable(lexer->c))
			return (lexer_collect_string(lexer));
		if (lexer->c == '<')
			return (help1_next_token(lexer));
		else if (lexer->c == '>')
			return (help2_next_token(lexer));
		else if (lexer->c == '|')
			return (lexer_advance_current(lexer, TOKEN_PIPE));
		else if (lexer->c == '\0')
			break ;
	}
	return (init_token(0, TOKEN_EOF));
}
