/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:59:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/22 16:08:57 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_qoute(char* src, int *i, t_envp* my_env)
{
	if (src[*i] == '\'')
	{
		i++;
		if (src[*i] == '\0')
		{
			printf("minishell: syntax error near unexpected token `\''\n");
			my_env->status = 1;
			return (-1);
		}
		if (src[*i] == '\'')
			i++;
		else
		{	
			while(src[*i] != '\'' && src[*i] != '\0')
			{
				i++;
				if (src[*i] == '\0')
				{
					printf("minishell: syntax error near unexpected token `\''\n");
					my_env->status = 1;
					return (-1);
				}
			}
			i++;
		}
	}
	return (0);
}

int	double_qoute(char* src, int i, t_envp* my_env)
{
	if (src[i] == '"')
	{
		i++;
		if (src[i] == '\0')
		{
			printf("minishell: syntax error near unexpected token `\"'\n");
			my_env->status = 1;
			return (-1);
		}
		if (src[i] == '"')
			i++;
		else
		{
			while(src[i] != '"' && src[i] != '\0')
			{
				i++;
				if (src[i] == '\0')
				{
					printf("minishell: syntax error near unexpected token `\"'\n");
					my_env->status = 1;
					return (-1);
				}
			}	
			i++;
		}
	}
	return (0);
}

int	unclosed_quotes(char* src, t_envp* my_env)
{
	int	i;

	i = 0;
	while(src[i])
	{
		while(src[i] != '\'' && src[i] != '"' && src[i])
			i++;

		// if (single_qoute(src, &i, my_env) == -1)
		// 	return (-1);
		// if (double_qoute(src, i, my_env) == -1)
		// 	return (-1);
		
		if (src[i] == '\'')
		{
			i++;
			if (src[i] == '\0')
			{
				printf("minishell: syntax error near unexpected token `\''\n");
				my_env->status = 1;
				return (-1);
			}
			if (src[i] == '\'')
				i++;
			else
			{	
				while(src[i] != '\'' && src[i] != '\0')
				{
					i++;
					if (src[i] == '\0')
					{
						printf("minishell: syntax error near unexpected token `\''\n");
						my_env->status = 1;
						return (-1);
					}
				}
				i++;
			}
		}
		
		if (src[i] == '"')
		{
			i++;
			if (src[i] == '\0')
			{
				printf("minishell: syntax error near unexpected token `\"'\n");
				my_env->status = 1;
				return (-1);
			}
			if (src[i] == '"')
				i++;
			else
			{
				while(src[i] != '"' && src[i] != '\0')
				{
					i++;
					if (src[i] == '\0')
					{
						printf("minishell: syntax error near unexpected token `\"'\n");
						my_env->status = 1;
						return (-1);
					}
				}	
				i++;
			}
		}
	}
	return (0);
}

int	check_syntax_error(char *src, t_envp* my_env, int *i)
{
	t_lexer*	lexer;
	t_lexer*	next_lexer;
	t_token*	token;
	t_token*	next_token;

	lexer = init_lexer(src);
	next_lexer = init_lexer(src);
	lexer->my_env = my_env;
	next_lexer->my_env = my_env;
	token = lexer_next_token(lexer);


	if (token->type == TOKEN_PIPE)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		my_env->status = 258;
		*i = lexer->i;
		return (-1);
	}
	next_token = lexer_next_token(next_lexer);
	while(token->type != TOKEN_EOF)
	{
		if (next_lexer->c == ' ')
			lexer_skip_whitespace(next_lexer);
		next_token = lexer_next_token(next_lexer);
		if (token->type == TOKEN_PIPE && (next_token->type == TOKEN_PIPE || !next_token->value))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			my_env->status = 258;
			*i = lexer->i;
			return (-1);
		}
		if ((token->type == TOKEN_HERDOC || token->type == TOKEN_IN || token->type == TOKEN_OU || token->type == TOKEN_APPAND || token->type == TOKEN_PIPE) &&
				(!next_token->value))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			my_env->status = 258;
			*i = lexer->i;
			return (-1);
		}
		if ((token->type == TOKEN_HERDOC || token->type == TOKEN_IN || token->type == TOKEN_OU || token->type == TOKEN_APPAND) &&
				(next_token->type == TOKEN_HERDOC || next_token->type == TOKEN_IN || next_token->type == TOKEN_OU ||
					next_token->type == TOKEN_APPAND  || next_token->type == TOKEN_PIPE))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", next_token->value);
			my_env->status = 258;
			*i = lexer->i;
			return (-1);
		}
		token = lexer_next_token(lexer);
	}
	if (unclosed_quotes(src, my_env) == -1)
		return(-1);
	return (0);
}