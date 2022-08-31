/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:29:41 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/29 21:29:51 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char**	ft_realloc(char	**s)
{
	int		i;
	int		k;
	char	**str;
	
	i = 0;
	k = ft_d_strlen(s);
	str = malloc((k + 2) * sizeof(char*));
	while (s[i])
	{
		str[i] = ft_strdup(s[i]);
		i++;
	}
	free(s);
	return (str);
}