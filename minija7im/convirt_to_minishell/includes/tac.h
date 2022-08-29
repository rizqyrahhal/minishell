/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:30 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/29 04:18:49 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAC_H
#define TAC_H

#include "libft.h"
#include "lexer.h"
#include "parser.h"

typedef struct s_tac
{
	t_lexer*	lexer;
	t_token*	token;
	t_command*	list;
	t_parser*	parser;
} t_tac;


void	tac_compile(char* src);
void	print_node(t_command *lst);

#endif