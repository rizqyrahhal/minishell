/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:00:53 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 14:48:29 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int	rand__(void)
{
	static unsigned long int	next;

	next += 1;
	next = next * 1103515245 + 12345;
	return ((unsigned int)(next / 65536) % 32768);
}

char	*ft_randstring(size_t length)
{
	char	*s;
	char	*str;
	size_t	i;
	int		k;

	s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	i = 0;
	str = malloc(length + 1);
	while (i < length)
	{
		k = rand__() % 62;
		str[i] = s[k];
		i++;
	}
	str[i] = 0;
	return (str);
}
