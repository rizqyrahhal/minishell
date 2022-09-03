/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:30:11 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/01 00:45:29 by rarahhal         ###   ########.fr       */
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
	char	*name_of_file;
} t_parser;

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list);
// t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list);

#endif


// < ffdgfg < dsfsg < fgfdg ls < dsgdfg -l < sgfg < test.txt       -a
// < ffdgfg < dsfsg < fgfdg ls < dsgdfg -l < sgfg < test.txt       -a | cat sdflhs < fpkwef
// < infile cmd1 -flag1 flag2 < test.txt | cmd2 