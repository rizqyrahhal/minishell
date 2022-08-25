/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:30:11 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 00:54:41 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "struct.h"

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list);
t_command	*ft_lstnew(char *s, int infile, int outfile);
void		ft_addfront(t_command	**list, t_command *new);

#endif
