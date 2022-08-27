/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/27 03:17:13 by rarahhal         ###   ########.fr       */
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

// strdup
#include <string.h>

/*   After break =======>> 
est apre n9ad lallocation dyal t_parser (outfile et infile ===== kaykhorjo 3la ranj chi marrat)
*/

void	free_parser(t_parser* parser)
{
	int	i;

	i = -1;
	while (parser->cmd[++i]){
		free(parser->cmd[i]);
	}
	free(parser->cmd);
	free(parser);
}

t_parser*	ft_rediriction(t_lexer* lexer, t_token* token, t_parser* parser)
{
	t_token*	next_token;

	printf("_-------------------_\n");
	//  this will fill the infile till the end and will get the last one
	if (token->type == TOKEN_IN)
	{
		if(parser->infile != 0){
			close(parser->infile);
		}
		if ((next_token = lexer_next_token(lexer))->type == TOKEN_STRING)
			parser->infile = open(next_token->value, O_RDONLY | O_TRUNC, 0600);
		printf("TOKEN_VALUE: %s\nNUMBER_OF_FD: %d\n", next_token->value, parser->infile);
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

	// if (token->type == TOKEN_HERDOC)
	// {
	// 	handl here_doce here
	// }

	// if (infile = -1)
	// {
	// 	move_to_next_cmd();
	/* in cas des error in open file :::: ghndir next token fwa7d lope 7ata l3nd TOKEN_PIPE OR TOKEN_EOF
	sabab hadchi howa ana ay cmd msta9ala bdatha wo ila kan chi error fchi cmd kt7bs 3and lERROR ms bash kydoz lnext pipe 
	bma3nd akhor ila khrajt fchi error fi l cmd li khadam fiha ghnprintih wo ndoz l next cmd*/
	// }
	return (parser);
}

t_command*	simple_command(t_lexer* lexer, t_token* token, t_command* list)
{
	t_parser*	parser;
	t_command*	new;
	int			i;

	i = 0;
	parser = ft_calloc(1, sizeof(t_parser));
	parser->cmd = ft_calloc(1, sizeof(char*));
	while(token->type != TOKEN_PIPE && token->type != TOKEN_EOF)
	{
		if (token->type == TOKEN_STRING)
		{
			parser->cmd = realloc(parser->cmd, i); /////// change par ft_realloc
			parser->cmd[i] = ft_strdup(token->value);
			i++;
		}
		parser = ft_rediriction(lexer, token, parser);
		token = lexer_next_token(lexer);
		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
	}
	parser->cmd[i] = NULL;
	new = ft_lstnew(parser->cmd, parser->infile, parser->outfile);
		ft_addfront(&list, new);
	// free_parser(parser);///      mfhamtch 3lach db salit manha walakin fach tanfriyiha ktkhssar data fi list
	return (list);
}

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list)
{
	
	/*                 ##!!!!!! DONT forgit HERE_DOC IN EUTCH COMMAND!!!!!!##       */
	printf("\n\n\n\n%s\n\n\n\n", token->value); ////////                    LMOCHKIL HNA MAKATRJA3CH LVALOR DYAL TOKEN KATB9A KIFMA KANT HNA 
	list = simple_command(lexer, token, list);
	while (token->type != TOKEN_EOF)
	{
		if (token->type == TOKEN_PIPE)
		{
		// function_simple_command;
		token = lexer_next_token(lexer);
		list = simple_command(lexer, token, list);
		// list = multi_command(lexer, token, list);//   comme simlpe just a simple defirent ---->  just assing not creat next node becouse is creat here	
		}
	}
	return (list);
}

		// printf("COMMAND: %s, INfile: %d, OUTfile: %d\n", list->cmd, list->input, list->output);








/*  ::::::::::::::::::::::::::::::::::::: ALGO OF SIMPLE_COMMAND  ::::::::::::::::::::::::::::::::::::::::::

hata nakhad data 3la khatri dyal lcomand kamlha 3ad nzidha fi list ila makan fiha 7ata error 
ila kan fiha chi error magahndawzhach lih bmara,
ghanrotirni error wo ndawoz lih ghi les CMD lis khashom ytexsicutaw

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