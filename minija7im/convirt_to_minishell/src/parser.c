/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/30 19:35:06 by rarahhal         ###   ########.fr       */
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

t_tac*	ft_rediriction(t_tac* tac)
{
	t_token*	next_token;
	char		*here_doc;

	if (tac->token->type == TOKEN_IN)
	{
		if(tac->parser->infile != 0){
			close(tac->parser->infile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->infile = open(next_token->value, O_RDONLY , 0600);
	}

	if (tac->token->type == TOKEN_OU)
	{
		if(tac->parser->outfile != 1){
			close(tac->parser->outfile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->outfile = open(next_token->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	
	if (tac->token->type == TOKEN_APPAND)
	{
		if(tac->parser->outfile != 1){
			close(tac->parser->outfile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->outfile = open(next_token->value, O_CREAT | O_RDWR | O_APPEND, 0644);
	}

	if (tac->token->type == TOKEN_HERDOC)
	{
		// handl here_doce here	
		tac->parser->infile = open(".temporere", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		// if (tac->parser->infile < 0)
			// return_error("ERR_HEREDOC");
		next_token = lexer_next_token(tac->lexer);
		while (1)
		{
			here_doc = readline("> ");
			if (!here_doc || !ft_strncmp(next_token->value, here_doc, ft_strlen(next_token->value) + 1))
				break ;
			write(tac->parser->infile, here_doc, ft_strlen(here_doc));
			write(tac->parser->infile, "\n", 1);
			free(here_doc);
		}
		free(here_doc);
		close(tac->parser->infile);
	// 	tac->parser->infile = open(".temporere", O_RDONLY);
	// 	if (tac->parser->infile < 0)
	// 	{
	// 		unlink(".temporere");
	// 		// return_error("ERR_heredoc_infile");
	// 	}
	}

	if (tac->parser->infile == -1)
	{
		printf("minishell: %s: No such file or directory\n", next_token->value);
		while (tac->token->type != TOKEN_PIPE && tac->token->type != TOKEN_EOF)
		{
			tac->token = lexer_next_token(tac->lexer);
		}
	}
	return (tac);
}

t_tac*	simple_command(t_tac* tac)
{
	t_command*	new;
	t_token*	next_token;
	int			i;

	i = 0;
	tac->parser = malloc(sizeof(t_parser));
	tac->parser->cmd = malloc(sizeof(char*));
	tac->parser->cmd[0] = NULL;
	tac->parser->infile = 0;
	tac->parser->outfile = 1;

	while(tac->token->type != TOKEN_PIPE && tac->token->type != TOKEN_EOF)
	{
		tac = ft_rediriction(tac);
		if (tac->token->type == TOKEN_STRING)
		{
			tac->parser->cmd = ft_realloc(tac->parser->cmd);
			tac->parser->cmd[i] = ft_strdup(tac->token->value);
			i++;
			tac->parser->cmd[i] = 0;
		}
			if (tac->token->type != TOKEN_EOF && tac->token->type != TOKEN_PIPE)
				tac->token = lexer_next_token(tac->lexer);
		// printf("A la fin de first while in simpele_command\n");
		// printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(tac->token));
	}
	if (tac->parser->infile != -1)
	{
		new = ft_lstnew(tac->parser->cmd, tac->parser->infile, tac->parser->outfile);
		ft_addfront(&tac->list, new);
	}
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
		// printf("DEMARE::::::::::::::::::::::::::::\n");
		// printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(tac->token));
		tac = simple_command(tac);
		if (tac->token->type == TOKEN_PIPE)
		{
			// printf("\n\nAFTER:  %s\n\n", tac->token->value);
			tac->token = lexer_next_token(tac->lexer);
		
			// printf("\n\nAPRE:   %s\n\n", tac->token->value);
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