/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/21 23:02:56 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tac.h"
#include "../includes/lexer.h"

void	tac_compile(char* src)
{
	t_lexer*	lexer;
	t_token*	token;

	lexer = init_lexer(src);
	token = lexer_next_token(lexer);
	while(token->type != TOKEN_EOF)
	{
		// sleep(1);
		printf("%s\n", token_to_str(token));
		sleep(1);
		token = lexer_next_token(lexer);
	}	
}
