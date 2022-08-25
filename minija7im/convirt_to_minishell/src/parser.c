/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 19:51:07 by rarahhal         ###   ########.fr       */
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
		if(infile != 0)
			close(infile);
		infile = open();
	}
	
	if (token->type == TOKEN_APPAND)
	{
		if(outfile != 1)
			close(outfile);
		outfile = open();///
	}
	
	if (token->type == TOKEN_OU)
	{
		if(outfile != 1)
			close(outfile);
		outfile = open();
	}
	
	if (infile = -1)
	{
		move_to_next_cmd(); 
	/* in cas des error in open file :::: ghndir next token fwa7d lope 7ata l3nd TOKEN_PIPE OR TOKEN_EOF
	sabab hadchi howa ana ay cmd msta9ala bdatha wo ila kan chi error fchi cmd kt7bs 3and lERROR ms bash kydoz lnext pipe 
	bma3nd akhor ila khrajt fchi error fi l cmd li khadam fiha ghnprintih wo ndoz l next cmd*/
	}
}

t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list)
{
	t_command*	new;
	int			infile = 0;
	int			outfile = 1;

	ft_rediriction(lexer, token, infile, outfile);
	if (token->type == TOKEN_STRING)
	{
		printf("___-- IN condition TOKEN_STRING --___\n");
		new = ft_lstnew(token->value, infile, outfile);
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