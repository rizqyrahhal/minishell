/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:08 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/17 22:25:55 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

t_token*	init_token(char* value, int type)
{
	t_token*	token;
	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;

	return (token);
}

const char* token_type_to_str(int type)
{
	if (type == '-')
		return "TOKEN_FLAGS";
	else if (type == '|')
		return "TOKEN_PIPE";
	else if (type == '"')
		return "TOKEN_DQ";
	else if (type == 39)
		return "TOKEN_SQ";
	else if (type == '<')
		return "TOKEN_IN";
	else if (type == '<<')
		return "TOKEN_HERDOC";
	else if (type == '>')
		return "TOKEN_OU";
	else if (type == '>>')
		return "TOKEN_APPAND";
	else if (type == '\0')
		return "TOKEN_EOF";
	else
		return "not_stringable";
}

char*	token_to_str(t_token* token)
{
	const char* type_str;
	const char* template;
	char* str;

	type_str = token_type_to_str(token->type);
	template = "type = %s,	int_type = %d,	value = %s";
	str = ft_calloc(ft_strlen(type_str) + ft_strlen(template) + 8, sizeof(char));
	sprintf(str, template, type_str, token->type, token->value);

	return str;
}