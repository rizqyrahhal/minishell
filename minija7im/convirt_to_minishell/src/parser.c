/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/29 23:36:54 by rarahhal         ###   ########.fr       */
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

	i = 0;
	while (parser->cmd[i]){
		free(parser->cmd[i]);
		i++;
	}
	free(parser->cmd);
	free(parser);
}

t_parser*	ft_rediriction(t_lexer* lexer, t_token* token, t_parser* parser)
{
	t_token*	next_token;

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
		// while (token->type != TOKEN_PIPE || token->type != TOKEN_EOF)
		// 	token = lexer_next_token(lexer);
	// 	move_to_next_cmd();
	/* in cas des error in open file :::: ghndir next token fwa7d lope 7ata l3nd TOKEN_PIPE OR TOKEN_EOF
	sabab hadchi howa ana ay cmd msta9ala bdatha wo ila kan chi error fchi cmd kt7bs 3and lERROR ms bash kydoz lnext pipe 
	bma3nd akhor ila khrajt fchi error fi l cmd li khadam fiha ghnprintih wo ndoz l next cmd*/
	// }
	return (parser);
}

t_tac*	simple_command(t_tac* tac)
{
	t_command*	new;
	int			i;

	i = 0;
	tac->parser = malloc(sizeof(t_parser));
	tac->parser->cmd = malloc(sizeof(char*));
	tac->parser->cmd[0] = NULL;
	tac->parser->infile = 0;
	tac->parser->outfile = 1;

	while(tac->token->type != TOKEN_PIPE && tac->token->type != TOKEN_EOF)
	{
		tac->parser = ft_rediriction(tac->lexer, tac->token, tac->parser);
		if (tac->token->type == TOKEN_STRING)
		{
			printf("token_value: %s\n", tac->token->value);
			tac->parser->cmd = ft_realloc(tac->parser->cmd); /////// change par ft_realloc
			tac->parser->cmd[i] = ft_strdup(tac->token->value);
			i++;
			tac->parser->cmd[i] = 0;
		}
		if (tac->token->type != TOKEN_PIPE || tac->token->type != TOKEN_EOF)
			tac->token = lexer_next_token(tac->lexer);
		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(tac->token));
	}
	new = ft_lstnew(tac->parser->cmd, tac->parser->infile, tac->parser->outfile);
	ft_addfront(&tac->list, new);
	return (tac);
}

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list)
{
	t_tac*	tac;

	tac = (t_tac*)malloc(sizeof(t_tac));
	tac->lexer = lexer;
	tac->token = token;
	tac->list = list;
	while (tac->token->type != TOKEN_EOF)
	{
		tac = simple_command(tac);
		if (tac->token->type == TOKEN_PIPE)
		{
			// printf("\n\nAFTER:  %s\n\n", tac->token->value); ////////                    LMOCHKIL HNA MAKATRJA3CH LVALOR DYAL TOKEN KATB9A KIFMA KANT HNA 

			tac->token = lexer_next_token(tac->lexer);
		
			// printf("\n\nAPRE:   %s\n\n", tac->token->value); ////////                    LMOCHKIL HNA MAKATRJA3CH LVALOR DYAL TOKEN KATB9A KIFMA KANT HNA 
		}
		if (tac->parser)
			free_parser(tac->parser);
	}

	return (tac->list);
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