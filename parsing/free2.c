/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:45:52 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/11 16:24:48 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*_free_value(char *value)
{
	char	*new;

	new = ft_strdup(value);
	free(value);
	return (new);
}

void	_tac_free(t_lexer **lexer, t_token **token, char *src)
{
	free(*lexer);
	free((*token)->value);
	free(*token);
	if (src)
		free(src);
}
