/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/26 16:52:22 by rarahhal         ###   ########.fr       */
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
// close
#include <unistd.h>

t_command*	ft_rediriction(t_lexer* lexer, t_token* token, t_command* list)
{
	t_token*	next_token;

	//  this will fill the infile till the end and will get the last one
	if (token->type == TOKEN_IN)
	{
		if(list->infile != 0){
			printf("_-------------------_\n");
			close(list->infile);
		}
		if ((next_token = lexer_next_token(lexer))->type == TOKEN_STRING)
			list->infile = open(next_token->value, O_RDONLY | O_TRUNC, 0600);
		printf("TOKEN_VALUE: %s\nNUMBER_OF_FD: %d\n", next_token->value, list->infile);
	}

	// if (token->type == TOKEN_APPAND)
	// {
	// 	if(outfile != 1)
	// 		close(outfile);
	// 	outfile = open();///
	// }

	// if (token->type == TOKEN_OU)
	// {
	// 	if(outfile != 1)
	// 		close(outfile);
	// 	outfile = open();
	// }

	// if (infile = -1)
	// {
	// 	move_to_next_cmd();
	/* in cas des error in open file :::: ghndir next token fwa7d lope 7ata l3nd TOKEN_PIPE OR TOKEN_EOF
	sabab hadchi howa ana ay cmd msta9ala bdatha wo ila kan chi error fchi cmd kt7bs 3and lERROR ms bash kydoz lnext pipe 
	bma3nd akhor ila khrajt fchi error fi l cmd li khadam fiha ghnprintih wo ndoz l next cmd*/
	// }
	return (list);
}

t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list)
{
	t_command*	new;
	int			counter;
	// t_parser*	parser;

	// parser = (t_parser*)malloc(sizeof(t_parser));
	// parser->infile = 0;
	// parser->outfile = 1;
	counter = 0;
	while(token->type != TOKEN_PIPE && token->type != TOKEN_EOF)
	{
		list = ft_rediriction(lexer, token, list);
		// first parametre
		if (token->type == TOKEN_STRING)
		{
			printf("___-- IN condition TOKEN_STRING --___\n");
			list->cmd = token->value;
			// new = ft_lstnew(token->value, 0, 1);   //// use realooc pour ajout anothre flag
			// ft_addfront(&list, new);
		}
		token = lexer_next_token(lexer);
		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
	}
	return (list);
}

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list)
{
	t_command*	new;

	if (token->type == TOKEN_APPAND || token->type == TOKEN_IN || token->type == TOKEN_OU || token->type == TOKEN_STRING)
	{
		/*
		mli nl9a | ghanzid node wo ndoze lsempel command i7timal wo sf
		*/
		new = ft_lstnew(token->value, 0, 1);   //// use realooc pour ajout anothre flag
			ft_addfront(&list, new);
		list = simple_command(lexer, token, list);

		if (token->type == TOKEN_PIPE)
		{
			// function_simple_command;
			new = ft_lstnew(token->value, 0, 1);
			ft_addfront(&list, new);
			list = simple_command(lexer, token, list);
			// list = multi_command(lexer, token, list);//   comme simlpe just a simple defirent ---->  just assing not creat next node becouse is creat here
		}
	}

	return (list);
}

		// printf("COMMAND: %s, INfile: %d, OUTfile: %d\n", list->cmd, list->input, list->output);








/*  ::::::::::::::::::::::::::::::::::::: ALGO OF SIMPLE_COMMAND  ::::::::::::::::::::::::::::::::::::::::::




*/


































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