/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 20:28:49 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/27 18:20:00 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_heredoc	*creat__file(t_heredoc *here, char *src, int stop)
{
	here->del_to_name = ft_randstring(8);
	if (here->i + 2 < stop)
		here->fd = open(here->del_to_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	here->str = ft_d_realloc(here->str);
	here->str = ft_d_realloc(here->str);
	here->str[here->j++] = src[here->i++];
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
	return (here);
}

t_heredoc	*get_delemeter(t_heredoc *here, char *src)
{
	while (src[here->i] && (int)here->lexer->i <= here->i)
		here->token = lexer_next_token(here->lexer);
	if (!src[here->i])
		return (NULL);
	here->i += ft_strlen(here->token->value) + 2;
	return (here);
}
