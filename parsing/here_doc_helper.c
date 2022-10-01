/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:28:49 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 13:36:12 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_filename(void)
{
	char	*rand_str;
	char	*file_name;

	rand_str = ft_randstring(8);
	file_name = ft_strjoin("/tmp/_", rand_str);
	free(rand_str);
	return (file_name);
}

t_heredoc	*creat__file(t_heredoc *here, char *src, int stop)
{
	here->del_to_name = get_filename();
	if (here->i + 2 < stop)
		here->fd = open(here->del_to_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	here->str = ft_d_realloc(here->str);
	here->str[here->j++] = src[here->i++];
	here->str[here->j] = '\0';
	here->str = ft_d_realloc(here->str);
	here->str[here->j++] = src[here->i++];
	here->str[here->j] = '\0';
	while (src && src[here->i] && (src[here->i] == ' ' || src[here->i] == '\t'))
	{
		here->str = ft_d_realloc(here->str);
		here->str[here->j++] = src[here->i++];
		here->str[here->j] = '\0';
	}
	here->k = 0;
	while (here->del_to_name && here->del_to_name[here->k] && here->i < stop)
	{
		here->str = ft_d_realloc(here->str);
		here->str[here->j++] = here->del_to_name[here->k++];
		here->str[here->j] = '\0';
	}
	free(here->del_to_name);
	return (get_delemeter(here, src));
}

int	count_(char *src, int i)
{
	int	count;

	count = 0;
	while (src[i] && src[i] != ' ')
	{
		if (src[i] == '\'')
		{
			i++;
			while (src[i] != '\'')
				i++;
			count += 2;
		}				
		if (src[i] == '"')
		{
			i++;
			while (src[i] != '"')
				i++;
			count += 2;
		}
		i++;
	}
	return (count);
}

t_heredoc	*get_delemeter(t_heredoc *here, char *src)
{
	int	qout;

	qout = count_(src, here->i);
	while (src[here->i] && (int)here->lexer->i <= here->i)
	{
		if (here->token->value)
			free(here->token->value);
		free(here->token);
		here->token = lexer_next_token(here->lexer);
	}
	if (src && !src[here->i])
	{
		_tokenfree_(&here);
		return (NULL);
	}
	here->i += ft_strlen(here->token->value) + qout;
	return (here);
}
