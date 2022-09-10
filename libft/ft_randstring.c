/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:00:53 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/10 17:24:46 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int	MyRand(unsigned int start_range,unsigned int end_range)
{
    static unsigned int	rand;

	rand += 44257; /* Any nonzero start state will work. */
    /*check for valid range.*/
	if(start_range == end_range)
		return start_range;

    /*get the random in end-range.*/
    rand += 941;
    rand %= end_range;

    /*get the random in start-range.*/
    while(rand < start_range)
        rand = rand + end_range - start_range;
	// printf("rand --- : %u\n", rand);
	return (rand);
}

int	ft_rand(void)
{
	return ((int)MyRand(0, 1000));
}

char *ft_randstring(size_t length)
{
    static char	*charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char		*randomString;
	int			n;

	randomString = NULL;
	if (length)
	{
		randomString = malloc(sizeof(char) * (length +1));
        if (randomString)
		{
            for (int n = 0;n < length;n++) {            
                int key = ft_rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
            randomString[length] = '\0';
        }
    }

    return randomString;
}