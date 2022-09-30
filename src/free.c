/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:04:24 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/30 21:35:15 by rarahhal         ###   ########.fr       */
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

void	_free_(t_tac **tac, t_token **token, int k)
{
	free((*token)->value);
	free(*token);
	if (k)
		free(*tac);
}
