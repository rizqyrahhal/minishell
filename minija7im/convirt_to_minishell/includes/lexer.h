/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:08:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/17 20:13:18 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

#define MAX(a, b)\
   a > b ? a : b

#define MIN(a, b)\
   a < b ? a : b

#include "libft.h"
#include "token.h"

typedef struct s_lexer
{
	char*			src;
	size_t			src_size;
	char			c;
	unsigned int	i;
} t_lexer;

t_lexer*	init_lexer(char* src);
void		lexer_advance(t_lexer* lexer);
void		lexer_skip_whitespace(t_lexer* lexer);
char		lexer_peek(t_lexer* lexer, int offset);
t_token*	lexer_advance_with(t_lexer* lexer, t_token* token);
t_lexer*	lexer_advance_current(t_lexer* lexer, int type);
t_token*	lexer_next_token(t_lexer* lexer);

#endif
