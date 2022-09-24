/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/24 17:00:02 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	int k = tac->lexer->i;
	char *str = NULL;
	int f = 0;
	while (tac->lexer->src[k] == ' ' && tac->lexer->src[k])
		k++;
	int p = k;
	if (tac->lexer->src[k] == '$')
	{
		while(tac->lexer->src[p] != ' ' && tac->lexer->src[p])
			p++;
		str = malloc(p - k + 1);
		while(tac->lexer->src[k] != ' ' && tac->lexer->src[k])
			str[f++] = tac->lexer->src[k++];
	}

	if (tac->token->type == TOKEN_IN || tac->token->type == TOKEN_HERDOC)
	{
		if(tac->parser->infile != 0){
			close(tac->parser->infile);
		}
		if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->infile = open(next_token->value, O_RDONLY, 0600);
	}

	
	if (tac->token->type == TOKEN_OU)
	{
		tac->parser->no_assign = 0;
		if(tac->parser->outfile != 1){
			close(tac->parser->outfile);
		}
		char* value;
		value = get_string(tac->lexer->my_env, str, 0);
		if (value && value[0]){
			tac->parser->outfile = open(value,  O_CREAT | O_RDWR | O_TRUNC , 0644);
			lexer_next_token(tac->lexer);
			if (tac->parser->outfile == -1)
			{
				perror(ft_strjoin("minishell: ", value));
				tac->lexer->my_env->status = 1;
				tac->parser->no_assign = -404;
			}
		}
		else if (str){
			printf("minishell: %s: ambiguous redirect\n", str);
			tac->lexer->my_env->status = 1;
			tac->parser->no_assign = -1;
			tac->parser->outfile = -1;
		}
		else if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->outfile = open(next_token->value,  O_CREAT | O_RDWR | O_TRUNC , 0644);
		if (tac->parser->outfile == -1 && tac->parser->no_assign > -1)
		{
			perror(ft_strjoin("minishell: ", next_token->value));
			tac->lexer->my_env->status = 1;
			tac->parser->no_assign = -1;
		}
	}

	if (tac->token->type == TOKEN_APPAND)
	{
		tac->parser->no_assign = 0;
		if(tac->parser->outfile != 1){
			close(tac->parser->outfile);
		}
		char* value;
		value = get_string(tac->lexer->my_env, str, 0);
		if (value && value[0]){
			tac->parser->outfile = open(value,  O_CREAT | O_RDWR | O_APPEND , 0644);
			lexer_next_token(tac->lexer);
			if (tac->parser->outfile == -1)
			{
				perror(ft_strjoin("minishell: ", value));
				tac->lexer->my_env->status = 1;
				tac->parser->no_assign = -404;
			}
		}
		else if (str){
			printf("minishell: %s: ambiguous redirect\n", str);
			tac->lexer->my_env->status = 1;
			tac->parser->no_assign = -1;
			tac->parser->outfile = -1;
		}
		else if ((next_token = lexer_next_token(tac->lexer))->type == TOKEN_STRING)
			tac->parser->outfile = open(next_token->value,  O_CREAT | O_RDWR | O_APPEND , 0644);
		if (tac->parser->outfile == -1 && tac->parser->no_assign > -1)
		{
			perror(ft_strjoin("minishell: ", next_token->value));
			tac->lexer->my_env->status = 1;
			tac->parser->no_assign = -1;
		}
	}

	if (tac->parser->infile == -1)
	{
		char* value;
		value = get_string(tac->lexer->my_env, str, 0);
		if (value && value[0])
			printf("minishell: %s: No such file or directory\n", value);
		else if (str)
			printf("minishell: %s: ambiguous redirect\n", str);
		else
			printf("minishell: %s: No such file or directory\n", next_token->value);
		tac->lexer->my_env->status = 1;
	}

	if (tac->parser->infile == -1 || tac->parser->outfile == -1 || tac->parser->no_assign == -1)
		while (tac->token->type != TOKEN_PIPE && tac->token->type != TOKEN_EOF) // move to next command after pipe |
			tac->token = lexer_next_token(tac->lexer);
	return (tac);
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
		tac = ft_rediriction(tac);
		lexer_skip_whitespace(tac->lexer);
		if (tac->token->type == TOKEN_STRING && tac->token->value[0] != 15)
		{
			tac->parser->splite[i] = 0;
			tac->parser->cmd = ft_realloc(tac->parser->cmd);
			tac->parser->cmd[i] = ft_strdup(tac->token->value);
			if (tac->lexer->spliter == -1)
				tac->parser->splite[i] = 1;
			i++;
			tac->parser->cmd[i] = 0;
			tac->parser->splite[i] = -2;
		}
		if (tac->token->type != TOKEN_EOF && tac->token->type != TOKEN_PIPE)
			tac->token = lexer_next_token(tac->lexer);
	}
	if (tac->parser->infile != -1 && tac->parser->cmd[0] != NULL && tac->parser->no_assign > -1)
	{
		new = ft_lstnew(tac->parser->cmd, tac->parser->infile, tac->parser->outfile);
		for (int l = 0; tac->parser->splite[l] != -2; l++){
			new->splite[l] = tac->parser->splite[l];
		}
		new->madir_walo = 0;
		ft_addfront(&tac->list, new);
	}
	else
	{
		new = ft_lstnew(NULL, 0, 1);
		new->madir_walo = -404;
		ft_addfront(&tac->list, new);
	}
	tac->parser->no_assign = 0;
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
		if (tac->token->type == TOKEN_PIPE){
			tac->lexer->my_env->num_pipe++;
			tac->token = lexer_next_token(tac->lexer);
		}
		if (tac->parser){
			free_parser(tac->parser);
		}
	}
	return (tac->list);
}
