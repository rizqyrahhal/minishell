/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/10 18:21:59 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	/* EXAMPLE GHAYKHASSAR LBLAN:   (ls << l > outtttt | cat << y > oufffff < infffff),
	daba hna kykhass ytkriya outfile 3ad ytprinta error dyal infile, 
	ALORS ----> makayn 7ata 7al mn ghir ndawoz lhabib ga3 les file bash ykon 3ando tartib dyalhom*/
	// HERE_DOC ghanakhod akhir file name 9adit wo man ttabi3t l7al ghankon m7it lakhrin wo ghanzido fi l **array dyal infile

	if (tac->token->type == TOKEN_IN)
	{
		if(tac->parser->infile != 0){
			close(tac->parser->infile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->infile = open(next_token->value, O_RDONLY, 0600);
	}

	if (tac->token->type == TOKEN_OU)
	{
		if(tac->parser->outfile != 1){
			close(tac->parser->outfile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->outfile = open(next_token->value,  O_CREAT | O_RDWR | O_TRUNC, 0644);
		// if(tac->parser->name_of_file != NULL)
		// 	ft_calloc(ft_strlen(tac->parser->name_of_file), sizeof(char));
		// if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
		// 	tac->parser->name_of_file = ft_strdup(next_token->value);
	}

	if (tac->token->type == TOKEN_APPAND)
	{
		if(tac->parser->outfile != 1){
			close(tac->parser->outfile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->outfile = open(next_token->value, O_CREAT | O_RDWR | O_APPEND, 0644);
	}

	/*
	HERE_DOC kysali ila dart (control + c) wo had lblan ya2ima khasso here_doc ykon f childe prossece ya ima chi 7al akhor b7al kif taydir bash
	L7AL howa mni nkon fi lhirdoc (cntl + c) OR (cntl + d) ghykono kykhorjo ghi mn here_doc wo appar here_doc ydiro khadmathoom
	
	!!!!!!! in bash tout HERE_DOC ktftah 9bal parssing dyal line !!!!!!!!!
	-----> CTRL+D : est un delemeter de here_doc (ya3ni ghanzid siognal dyalha fi condition bash ywa9f print b7al delimeter wo sf).
	-----> CTRL+C : kat anelee ay 7aja mn binha here_doc alor madam l here_doc fi bash kythandlo 9bal parsin dyal line,
	idan fa  khasni mn opnich les outfile ila kan chi here_doc mn ba3d chi wo7din wo 7bas bi CTRL+C.

	(L7OLOL :):) ----__--> 1) (***) ima ghnchiki ila kant ctrl+c wo tfat7o chi filat nm7ihom 
	(L7OLOL :):) ----__--> 2) (*****) in lexer opning here_doc and save your files with delimitre like name,
	and handl it apre in parsing like infile  

	// FILE POUR STOCK HERE_DOC "/tmp/sh-thd-1641928925"
	*/


	if (tac->token->type == TOKEN_HERDOC)
	{
		if (tac->parser->infile != 0)
			close(tac->parser->infile);
		char*	tmpstr = ft_randstring(8);
		tac->parser->infile = open(tmpstr, O_CREAT | O_RDWR | O_TRUNC, 0644);
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
		tac->parser->infile = open(tmpstr , O_RDONLY, 0600);
		if (tac->parser->infile < 0)
		{
			unlink(tmpstr);
			printf("ERR_heredoc_infile\n");
		}
	}

	if (tac->parser->infile == -1)
	{
		printf("minishell: %s: No such file or directory\n", next_token->value);
		tac->lexer->my_env->status = 1;
		while (tac->token->type != TOKEN_PIPE && tac->token->type != TOKEN_EOF) // move to next command after pipe |
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
	if (tac->parser->infile != -1 && tac->parser->cmd[0] != NULL)
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