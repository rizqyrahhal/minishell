/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:08 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/20 00:27:15 by rarahhal         ###   ########.fr       */
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
	if (type == TOKEN_STRING)
		return "TOKEN_STRING";
	else if (type == TOKEN_PIPE)
		return "TOKEN_PIPE";
	else if (type == TOKEN_DQ)
		return "TOKEN_DQ";
	else if (type == TOKEN_SQ)
		return "TOKEN_SQ";
	else if (type == TOKEN_IN)
		return "TOKEN_IN";
	else if (type == TOKEN_HERDOC)
		return "TOKEN_HERDOC";
	else if (type == TOKEN_OU)
		return "TOKEN_OU";
	else if (type == TOKEN_APPAND)
		return "TOKEN_APPAND";
	// else if (type == TOKEN_ENV_VARIABLE)
	// 	return "TOKEN_ENV_VARIABLE";	
	else if (type == TOKEN_EOF)
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