/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 18:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/27 14:01:20 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parser(t_parser *parser)
{
	int	i;

	i = 0;
	while (parser->cmd[i])
	{
		free(parser->cmd[i]);
		i++;
	}
	free(parser->cmd);
	free(parser);
}

t_tac	*parese_command(t_tac *tac)
{
	int	i;

	i = 0;
	while (tac->token->e_type != TOKEN_PIPE && tac->token->e_type != TOKEN_EOF)
	{
		tac = ft_rediriction(tac);
		lexer_skip_whitespace(tac->lexer);
		if (tac->token->e_type == TOKEN_STRING && tac->token->value[0] != 15)
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
		if (tac->token->e_type != TOKEN_EOF && tac->token->e_type != TOKEN_PIPE)
			tac->token = lexer_next_token(tac->lexer);
	}
	return (tac);
}

t_tac	*cmd_to_list(t_tac *tac)
{
	t_command	*new;
	int			i;

	i = 0;
	new = ft_lstnew(tac->parser->cmd, tac->parser->infile,
			tac->parser->outfile);
	while (tac->parser->splite[i] != -2)
	{
		new->splite[i] = tac->parser->splite[i];
		i++;
	}
	new->madir_walo = 0;
	ft_addfront(&tac->list, new);
	return (tac);
}

t_tac	*simple_command(t_tac *tac)
{
	t_command	*new;

	tac->parser = malloc(sizeof(t_parser));
	tac->parser->cmd = malloc(sizeof(char *));
	tac->parser->cmd[0] = NULL;
	tac->parser->infile = 0;
	tac->parser->outfile = 1;
	tac = parese_command(tac);
	if (tac->parser->infile != -1 && tac->parser->cmd[0] != NULL
		&& tac->parser->no_assign > -1)
		tac = cmd_to_list(tac);
	else
	{
		new = ft_lstnew(NULL, 0, 1);
		new->madir_walo = -404;
		ft_addfront(&tac->list, new);
	}
	tac->parser->no_assign = 0;
	return (tac);
}

t_command	*parser(t_lexer *lexer, t_token *token, t_command *list)
{
	t_tac	*tac;

	tac = (t_tac *)malloc(sizeof(t_tac));
	tac->lexer = lexer;
	tac->token = token;
	tac->list = list;
	while (tac->token->e_type != TOKEN_EOF)
	{
		tac = simple_command(tac);
		if (tac->token->e_type == TOKEN_PIPE)
		{
			tac->lexer->my_env->num_pipe++;
			tac->token = lexer_next_token(tac->lexer);
		}
		if (tac->parser)
			free_parser(tac->parser);
	}
	return (tac->list);
}
