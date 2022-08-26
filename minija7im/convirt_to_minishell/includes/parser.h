/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:30:11 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/26 23:49:34 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "struct.h"
#include "libft.h"
typedef struct s_parser
{
	char**	cmd;
	int		infile;
	int		outfile;
} t_parser;

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list);
// t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list);

#endif
