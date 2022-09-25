/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:00 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/25 13:55:33 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char*	get_string(t_envp *my_env, char *s, int count); ////// move to hedre

t_token* lexer_collect_string(t_lexer* lexer)
{
    char *value = ft_calloc(1, sizeof(char));
    unsigned int len = 0;
	int		count;

	count = 0;
	lexer->spliter = 0;
	while (ft_non_tokenable(lexer->c) && lexer->c != '\0')
	{
		// single qoute
		if (lexer->c == '\''){ ///////// Single Qoute '\''
    		lexer_advance(lexer);
    		while (lexer->c != '\0' && lexer->c != '\'') {
        		value = ft_d_realloc(value);
    	    	value[len++] = lexer->c;
    	    	lexer_advance(lexer);
    		}
			if (lexer->c == '\'')
    	    	lexer_advance(lexer);
			len = ft_strlen(value);
			count = len;
		}

		// double qoute
		if (lexer->c == '"'){
			lexer_advance(lexer);
    		while (lexer->c != '\0' && lexer->c != '"') {
        		value = ft_d_realloc(value);
    	    	value[len++] = lexer->c;
				value[len] = '\0';
    	    	lexer_advance(lexer);
    		}
			if (lexer->c == '"')
		    	lexer_advance(lexer);
			if (lexer->not_expand == 0)
				value = get_string(lexer->my_env, value, count);
			len = ft_strlen(value);
			count = len;
		}

		// not qouting
		if (ft_non_tokenable(lexer->c) && lexer->c != '\'' && lexer->c != '"' && lexer->c != '\0'){
			while(ft_non_tokenable(lexer->c) && lexer->c != '\'' && lexer->c != '"' && lexer->c != '\0')
			{
				if (lexer->c == '$' && (lexer->src[lexer->i + 1] == '"' || lexer->src[lexer->i + 1] == '\''))
					lexer_advance(lexer);
				else
        		{
					value = ft_d_realloc(value);
					value[len++] = lexer->c;
					value[len] = '\0';
					lexer_advance(lexer);
				}			
			}
			
			for (int i = 0; value[i] ; i++)
			{
				if (value[i] == '$'){
					lexer->spliter = -1;
                    break;
				}
			}
			if (lexer->not_expand == 0)
				value = get_string(lexer->my_env, value, count);
			if (lexer->c != '\'' && lexer->c != '"'){	
				if (value[0] == '\0')
					value[0] = 15;
			}
			len = ft_strlen(value);
			count = len;
		}
	}
    value[len] = '\0';
	return init_token(value, TOKEN_STRING);
}

void	lexer_skip_whitespace(t_lexer* lexer)
{
	while (lexer->c == 13 || lexer->c == 10 || lexer->c == ' ' || lexer->c == '\t')
		lexer_advance(lexer);
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

		if (ft_non_tokenable(lexer->c))
            return lexer_collect_string(lexer);

		if (lexer->c == '<')
		{
			if (lexer_peek(lexer, 1) == '<')
			{
				lexer->i += 1;
				return lexer_advance_with(lexer, init_token("<<", TOKEN_HERDOC));
			}
			else
				return lexer_advance_with(lexer, init_token("<", TOKEN_IN));
		}
		else if (lexer->c == '>')
		{
			if (lexer_peek(lexer, 1) == '>')
			{
				lexer->i += 1;
				return lexer_advance_with(lexer, init_token(">>", TOKEN_APPAND));
			}
			else
				return lexer_advance_with(lexer, init_token(">", TOKEN_OU));
		}
		else if (lexer->c == '|')
			return lexer_advance_current(lexer, TOKEN_PIPE);
		else if (lexer->c == '\0')
			break;
	}
	return (init_token(0, TOKEN_EOF));
}
