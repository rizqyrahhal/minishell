/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:00 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/19 05:05:48 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lexer.h"

t_lexer*	init_lexer(char* src)
{
	t_lexer* lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	lexer->src = src;
	lexer->src_size = ft_strlen(src);
	lexer->i = 0;
	lexer->c = src[lexer->i];

	return (lexer);
}

void	lexer_advance(t_lexer* lexer)
{
	if (lexer->i < lexer->src_size && lexer->c != '\0')
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer* lexer)
{
	while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
}

t_token* lexer_parse_id(t_lexer* lexer)
{
	char* value = ft_calloc(1, sizeof(char));
	
	// ft_isalpha(lexer->c) || ft_isdigit(lexer->c)
	while (ft_isalpha(lexer->c) || ft_isdigit(lexer->c))//// (!all_of_token(lexer->c, *token); pour assing all caracter  non_tokenable in one string) OR (change is_alpha par is_not_token(lexer->c))
	{
		value = realloc(value, (ft_strlen(value) + 2) * sizeof(char));
		strcat(value, (char[]){lexer->c, 0}); /////// change strcat
		lexer_advance(lexer);
	}

	return init_token(value, TOKEN_STRING);
}

char	lexer_peek(t_lexer* lexer, int offset)
{
	//  bash man9alabch kharj man size
	return (lexer->src[MIN(lexer->i + offset, lexer->src_size)]);
	// return lexer->src[i + 1] if exist or '\0'
}

t_token*	lexer_advance_with(t_lexer* lexer, t_token* token)
{
	lexer_advance(lexer);
	return token;
}

t_token*	lexer_advance_current(t_lexer* lexer, int type)
{
	char* value;
	t_token* token;
	
	value = ft_calloc(2, sizeof(char));
	value[0] = lexer->c;
	value[1] = '\0';
	token = init_token(value, type);
	lexer_advance(lexer);

	return token;
}

t_token*	lexer_next_token(t_lexer* lexer)
{
	while(lexer->c != '\0')
	{
		lexer_skip_whitespace(lexer);

		if (ft_isalpha(lexer->c) || ft_isdigit(lexer->c))
			return lexer_parse_id(lexer);///// after change is_alpha add this line in last else

		// number here

		if (lexer->c == '<')
		{
			if (lexer_peek(lexer, 1) == '<')
				return lexer_advance_with(lexer, init_token("<<", TOKEN_HERDOC));
			return lexer_advance_with(lexer, init_token("<", TOKEN_IN));
		}
		else if (lexer->c == '>')
		{
			if (lexer_peek(lexer, 1) == '>')
				return lexer_advance_with(lexer, init_token(">>", TOKEN_APPAND));
			return lexer_advance_with(lexer, init_token(">", TOKEN_OU));
		}
		else if (lexer->c == '-')
			return lexer_advance_current(lexer, TOKEN_FLAGS);
		else if (lexer->c == '|')
			return lexer_advance_current(lexer, TOKEN_PIPE);
		else if (lexer->c == '"')
			return lexer_advance_current(lexer, TOKEN_DQ);
		else if (lexer->c == 39)
			return lexer_advance_current(lexer, TOKEN_SQ);
		else if (lexer->c == '\0')
			break;
		// else
		// 	return lexer_parse_id(lexer);
		else
			printf("[Lexer]: Unexpected character `%c`\n", lexer->c); exit(1); break;
	}

	return (init_token(0, TOKEN_EOF));
}
