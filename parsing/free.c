/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:04:24 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 19:29:51 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	_free_(t_tac **tac, t_token **token, int k)
{
	free((*token)->value);
	free(*token);
	if (k)
		free(*tac);
}

void	_free_t_v(t_token **token, char **value)
{
	free((*token)->value);
	free(*token);
	free(*value);
}

void	_tokenfree_(t_heredoc **here)
{
	free((*here)->token->value);
	free((*here)->token);
	free((*here)->lexer);
	free((*here)->str);
	free(*here);
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

void	ft_free_(t_lexer *l, t_lexer *nl, t_token *t, t_token *nt)
{
	free(l);
	free(nl);
	free(t->value);
	free(t);
	free(nt->value);
	free(nt);
}
