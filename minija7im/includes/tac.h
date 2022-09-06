/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:30 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/06 14:25:00 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TAC_H
#define TAC_H

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "struct.h"

typedef struct s_tac
{
	t_lexer*	lexer;
	t_token*	token;
	t_command*	list;
	t_parser*	parser;
} t_tac;


void	tac_compile(char* src, t_envp* my_env);
void	print_node(t_command *lst);

#endif