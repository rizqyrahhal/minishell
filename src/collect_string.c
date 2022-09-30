/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:46:39 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/30 15:41:50 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../execut_libft/ex_libft.h"
#include "../includes/execution.h"

char	*singel_qoute(t_lexer *lexer, char *value, int *len, int *count)
{
	if (lexer->c == '\'')
	{
		lexer_advance(lexer);
		while (lexer->c != '\0' && lexer->c != '\'')
		{
			value = ft_d_realloc(value);
			value[*len] = lexer->c;
			*len += 1;
			value[*len] = '\0';
			lexer_advance(lexer);
		}
		if (lexer->c == '\'')
			lexer_advance(lexer);
		*len = ft_strlen(value);
		*count = *len;
	}
	return (value);
}

char	*_double_qoute(t_lexer *lexer, char *value, int *len, int *count)
{
	if (lexer->c == '"')
	{
		lexer_advance(lexer);
		while (lexer->c != '\0' && lexer->c != '"')
		{
			value = ft_d_realloc(value);
			value[*len] = lexer->c;
			*len += 1;
			value[*len] = '\0';
			lexer_advance(lexer);
		}
		if (lexer->c == '"')
			lexer_advance(lexer);
		if (lexer->not_expand == 0)
			value = get_string(lexer->my_env, value, *count);
		*len = ft_strlen(value);
		*count = *len;
	}
	return (value);
}

char	*non_qouting(t_lexer *lexer, char *value, int *len)
{
	while (ft_non_tokenable(lexer->c) && lexer->c != '\''
		&& lexer->c != '"' && lexer->c != '\0')
	{
		if (lexer->c == '$' && (lexer->src[lexer->i + 1] == '"'
				|| lexer->src[lexer->i + 1] == '\''))
			lexer_advance(lexer);
		else
		{
			value = ft_d_realloc(value);
			value[*len] = lexer->c;
			*len += 1;
			value[*len] = '\0';
			lexer_advance(lexer);
		}		
	}
	return (value);
}

char	*non_qouting2(t_lexer *lexer, char *value, int *count)
{
	int	m;

	if (sea_rch(value, '$'))
		lexer->spliter = -1;
	if (lexer->not_expand == 0)
	{
		while (value[*count] && value[*count] != '$')
			*count += 1;
		m = *count;
		while (value[m] && (ft_isalpha(value[m])
				|| ft_isdigit(value[m]) || value[m] == '_'))
			m++;
		if (value[m] && !ft_isalpha(value[m])
			&& !ft_isdigit(value[m]) && value[m] != '_')
			lexer->spliter = 0;
		value = get_string(lexer->my_env, value, *count);
	}
	if (lexer->c != '\'' && lexer->c != '"')
	{	
		if (value[0] == '\0')
			value[0] = 15;
	}
	return (value);
}

t_token	*lexer_collect_string(t_lexer *lexer)
{
	char	*value;
	int		len;
	int		count;

	value = ft_calloc(1, sizeof(char));
	len = 0;
	count = 0;
	lexer->spliter = 0;
	while (ft_non_tokenable(lexer->c) && lexer->c != '\0')
	{
		value = singel_qoute(lexer, value, &len, &count);
		value = _double_qoute(lexer, value, &len, &count);
		if (ft_non_tokenable(lexer->c) && lexer->c != '\''
			&& lexer->c != '"' && lexer->c != '\0')
		{
			value = non_qouting(lexer, value, &len);
			value = non_qouting2(lexer, value, &count);
			len = ft_strlen(value);
			count = len;
		}
	}
	value[len] = '\0';
	return (init_token(_free_value(value), TOKEN_STRING));
}
