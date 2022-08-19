/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:11:16 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/19 03:21:52 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
#define TOKEN_H

#include "libft.h"

typedef struct s_token
{
	char* value;
	enum
	{
		TOKEN_STRING,
		TOKEN_FLAGS, // - Flags of command
		TOKEN_PIPE, // | pipe
		TOKEN_DQ, // " double qoute
		TOKEN_SQ, // ' single qoute
		TOKEN_IN, // < inpute redirection
		TOKEN_HERDOC, // << her_doc
		TOKEN_OU, // > output redirection
		TOKEN_APPAND, // >> appandade output redirection
		TOKEN_ENV_VARIABLE, //  Variable expression
		// TOKEN_HIOME_DIR, // Home directory
		TOKEN_EOF, // end of file
	} type;
} t_token;

t_token*	init_token(char* value, int type);
char*		token_to_str(t_token* token);

#endif