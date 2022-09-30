/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediriction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 20:21:06 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/30 17:07:29 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*file_name(t_lexer *lexer)
{
	int		k;
	char	*str;
	int		f;
	int		p;

	k = lexer->i;
	str = NULL;
	f = 0;
	while (lexer->src[k] == ' ' && lexer->src[k])
		k++;
	p = k;
	if (lexer->src[k] == '$')
	{
		while (lexer->src[p] != ' ' && lexer->src[p])
			p++;
		str = malloc(p - k + 1);
		while (lexer->src[k] != ' ' && lexer->src[k])
			str[f++] = lexer->src[k++];
	}
	return (str);
}

t_tac	*help_outfile(t_tac *tac, char *str, char *value, int flag)
{
	if (value && value[0])
	{
		tac->parser->outfile = open(value, O_CREAT | O_RDWR | flag, 0644);
		lexer_next_token(tac->lexer);
		if (tac->parser->outfile == -1)
		{
			perror(ft_strjoin("minishell: ", value));
			tac->lexer->my_env->status = 1;
			tac->parser->no_assign = -404;
		}
	}
	else if (str)
	{
		printf("minishell: %s: ambiguous redirect\n", str);
		tac->lexer->my_env->status = 1;
		tac->parser->no_assign = -1;
		tac->parser->outfile = -1;
	}
	return (tac);
}

t_tac	*ouftile_tokens(t_tac *tac, char *str, int flag)
{
	char	*value;
	t_token	*next_token;
	char	*join;

	join = NULL;
	next_token = lexer_next_token(tac->lexer);
	tac->parser->no_assign = 0;
	if (tac->parser->outfile != 1)
		close(tac->parser->outfile);
	value = get_string(tac->lexer->my_env, str, 0);
	if ((value && value[0]) || str)
		help_outfile(tac, str, value, flag);
	else if (next_token->e_type == TOKEN_STRING)
		tac->parser->outfile = open(next_token->value, O_CREAT
				| O_RDWR | flag, 0644);
	if (tac->parser->outfile == -1 && tac->parser->no_assign > -1)
	{
		join = ft_strjoin("minishell: ", next_token->value);
		perror(join);
		free(join);
		tac->lexer->my_env->status = 1;
		tac->parser->no_assign = -1;
	}
	f_ree_(&next_token);
	return (tac);
}

t_tac	*infile_error(t_tac *tac, char *str, char *next_token)
{
	char	*value;

	if (tac->parser->infile == -1)
	{
		value = get_string(tac->lexer->my_env, str, 0);
		if (value && value[0])
			printf("minishell: %s: No such file or directory\n", value);
		else if (str)
			printf("minishell: %s: ambiguous redirect\n", str);
		else
			printf("minishell: %s: No such file or directory\n", next_token);
		tac->lexer->my_env->status = 1;
		free(value);
	}
	return (tac);
}

t_tac	*ft_rediriction(t_tac *tac)
{
	t_token	*next_token;
	char	*str;

	str = file_name(tac->lexer);
	next_token = init_token(NULL, 0);
	if (tac->token->e_type == TOKEN_IN || tac->token->e_type == TOKEN_HERDOC)
	{
		if (tac->parser->infile != 0)
			close(tac->parser->infile);
		free(next_token);
		next_token = lexer_next_token(tac->lexer);
		if (next_token->e_type == TOKEN_STRING)
			tac->parser->infile = open(next_token->value, O_RDONLY, 0600);
	}
	if (tac->token->e_type == TOKEN_OU)
		tac = ouftile_tokens(tac, str, O_TRUNC);
	if (tac->token->e_type == TOKEN_APPAND)
		tac = ouftile_tokens(tac, str, O_APPEND);
	tac = infile_error(tac, str, next_token->value);
	tac = next_command(&tac);
	free(next_token->value);
	free(next_token);
	return (tac);
}
