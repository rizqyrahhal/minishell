/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 21:29:41 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 18:40:29 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_realloc(char **s)
{
	int		i;
	int		k;
	char	**str;

	i = 0;
	k = ft_d_strlen(s);
	str = malloc((k + 2) * sizeof(char *));
	while (i < k)
	{
		str[i] = ft_strdup(s[i]);
		i++;
	}
	str[i] = 0;
	free_string(s);
	free(s);
	return (str);
}

char	*ft_d_realloc(char *s)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = ft_strlen(s);
	str = malloc((k + 2) * sizeof(char));
	while (i < k)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	free(s);
	return (str);
}
