/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 17:14:28 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/parser.h"
#include "../includes/tac.h"
#include "../includes/lexer.h"
#include "../include/struct.h"
#include <stdlib.h>

//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	ft_rediriction(t_lexer* lexer, t_token* token, int infile, int outfile)
{
	//  this will fill the infile till the end and will get the last one
	if (token->type == TOKEN_IN)
	{
		infile = open();
	}
	if (token->type == TOKEN_OU)
	{
		outfile = open();
	}
}

t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list)
{
	t_command*	new;
	int			infile = 0;
	int			outfile = 1;

	// if (token->type == TOKEN_IN || token->type == TOKEN_OU)
		// functoin pour handle rediriction;
	ft_rediriction(lexer, token, infile, outfile);
	if (token->type == TOKEN_STRING)
	{
		printf("___-- IN condition TOKEN_STRING --___\n");
		new = ft_lstnew(token->value, 0, 1);
		ft_addfront(&list, new);
	}
	return (list);
}

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list)
{
	list = simple_command(lexer, token, list);
	// if (token->type == TOKEN_PIPE)
		// function_simple_command;

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