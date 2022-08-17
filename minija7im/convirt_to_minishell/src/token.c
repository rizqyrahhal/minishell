/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:08 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/17 17:48:12 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/token.h"

t_token*	init_token(char* value, int type)
{
	t_token*	token;
	token = ft_calloc(1, sizeof(t_token));
	token->value = value;
	token->type = type;

	return (token);
}
