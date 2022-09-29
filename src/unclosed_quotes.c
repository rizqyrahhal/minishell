/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 00:17:54 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/28 17:24:54 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	single_qoute(char *src, int *i)
{
	if (src[*i] == '\'')
	{
		*i += 1;
		if (src[*i] == '\0')
			return (-1);
		if (src[*i] == '\'')
			*i += 1;
		else
		{	
			while (src[*i] != '\'' && src[*i] != '\0')
			{
				*i += 1;
				if (src[*i] == '\0')
					return (-1);
			}
			*i += 1;
		}
	}
	return (0);
}

int	double_qoute(char *src, int *i)
{
	if (src[*i] == '"')
	{
		*i += 1;
		if (src[*i] == '\0')
			return (-1);
		if (src[*i] == '"')
			*i += 1;
		else
		{
			while (src[*i] != '"' && src[*i] != '\0')
			{
				*i += 1;
				if (src[*i] == '\0')
					return (-1);
			}	
			*i += 1;
		}
	}
	return (0);
}

int	unclosed_quotes(char *src, int **k)
{
	int	i;

	i = 0;
	while (src[i])
	{
		while (src[i] != '\'' && src[i] != '"' && src[i])
			i++;
		**k = i;
		if (single_qoute(src, &i) == -1)
		{
			printf("minishell: syntax error near unexpected token `\''\n");
			return (-1);
		}
		if (double_qoute(src, &i) == -1)
		{
			printf("minishell: syntax error near unexpected token `\"'\n");
			return (-1);
		}
	}
	return (0);
}
