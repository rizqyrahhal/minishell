/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:08 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 19:29:51 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->e_type = type;
	return (token);
}
