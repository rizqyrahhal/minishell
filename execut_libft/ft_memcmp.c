/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:57:02 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/28 12:48:02 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && st1[i] == st2[i])
	{
		i++;
	}
	return (st1[i] - st2[i]);
}
