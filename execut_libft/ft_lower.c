/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lower.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:17:42 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 16:17:43 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

char	*lo_wer(char *s)
{
	int		i;
	char	*low;

	i = 0;
	low = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		if (ft_isalpha(s[i]))
			low[i] = ft_tolower(s[i]);
		else
			low[i] = s[i];
		i++;
	}
	low[i] = 0;
	return (low);
}
