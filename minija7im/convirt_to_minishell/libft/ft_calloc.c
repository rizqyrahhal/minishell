/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:24:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/17 17:36:33 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lbft.h"

void	ft_bzero(void	*s, size_t	n)
{
	unsigned char	*str;
	size_t			i;

	if (n != 0)
	{
		i = 0;
		str = s;
		while (i < n)
		{
			str[i] = 0;
			i++;
		}
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}