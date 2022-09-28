/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 11:04:01 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/28 12:48:11 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (d == NULL && s == NULL)
		return (0);
	if (s == d && len == 0)
		return (d);
	if (d > s)
	{
		while (len > 0)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	else if (d < s)
		ft_memcpy(d, s, len);
	return (dst);
}
