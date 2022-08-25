/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 01:50:36 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/parser.h"
#include "../includes/tac.h"
#include "../includes/lexer.h"
#include "../include/struct.h"
#include <stdlib.h>

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list)
{
	t_command*	new;
	t_token*	next_token;

	// next_token = lexer_next_token(lexer);
	// printf("next_token: %s   NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN\n", next_token->value);
	printf("token: %s   TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT\n", token->value);
	// if (token->type == TOKEN_IN || token->type == TOKEN_OU)
		// functoin pour handle rediriction;
	
	if (token->type == TOKEN_STRING)
	{
		printf("___-- IN condition TOKEN_STRING --___\n");
		new = ft_lstnew(token->value, 0, 1);
		if (lexer_next_token(lexer)->type != TOKEN_EOF)
			ft_addfront(&list, new);
	}
	// if (token->type == TOKEN_PIPE)
	// 	ft_addfront(&list, new);
	return (list);
}

		// printf("COMMAND: %s, INfile: %d, OUTfile: %d\n", list->cmd, list->input, list->output);












// t_command*	ft_lstlast(t_command *list)
// {
// 	while (list)
// 	{
// 		if (!list->next)
// 			return(list);
// 		list = list->next;
// 	}
// 	return (list);
// }

// void	ft_addfront(t_command	**list, t_command *new)
// {
// 	t_command*	tmp;
	
// 	if (*list == NULL)
// 		*list = new;
// 	else
// 	{
// 		if (*list)
// 		{
// 			tmp = ft_lstlast(*list);
// 			tmp->next = new;
// 		}
// 		else
// 			*list = new;
// 	}
// }

// t_command	*ft_lstnew(char *s, int infile, int outfile)
// {
// 	t_command*	n1;

// 	n1 = malloc(sizeof(t_command));
// 	if (n1 == 0)
// 		return (NULL);
// 	n1->cmd = malloc(ft_strlen(s));
// 	n1->cmd = s;
// 	n1->input = infile;
// 	n1->output = outfile;
// 	n1->next = NULL;
// 	return (n1);
// }