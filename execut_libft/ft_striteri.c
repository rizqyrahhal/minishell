/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:11:07 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 21:37:26 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t		i;
	size_t		p;

	if (!s)
		return ;
	p = ft_strlen(s);
	i = 0;
	while (i < p)
	{
		f(i, &s[i]);
		i++;
	}
}
