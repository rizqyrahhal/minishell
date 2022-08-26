/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:30:11 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/26 22:45:07 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "struct.h"

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list);
// t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list);

#endif
