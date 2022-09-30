/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:28:49 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/30 22:32:51 by rarahhal         ###   ########.fr       */
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
	while (src[here->i] && (src[here->i] == ' ' || src[here->i] == '\t'))
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
	return (get_delemeter(here, src));
}

t_heredoc	*get_delemeter(t_heredoc *here, char *src)
{
	int	qout;
	int	i;

	i = here->i;
	while (src[i] && src[i] != '"' && src[i] != '\'' && src[i] != ' ' && src[i] != '\t')
		i++;
	qout = 0;
	if (src[i] && (src[i] == '"' || src[i] == '\''))
		qout = 2;
	while (src[here->i] && (int)here->lexer->i <= here->i)
	{
		if (here->token->value)
			free(here->token->value);
		free(here->token);
		here->token = lexer_next_token(here->lexer);
	}
	if (!src[here->i])
		return (NULL);
	here->i += ft_strlen(here->token->value) + qout;
	return (here);
}

char	*_free_token(t_heredoc *here, char *src)
{
	free(here->token->value);
	free(here->token);
	free(here->lexer);
	src = ft_strdup(here->str);
	free(here->str);
	free(here);
	return (src);
}
