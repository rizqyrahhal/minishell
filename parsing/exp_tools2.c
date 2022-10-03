/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:42:36 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/02 09:58:35 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*ft_replace(char *s, char *old, char *new, int *k)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(s) + (ft_strlen(new) - ft_strlen(old)) + 1);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (j == *k - 1)
		{
			ft_strcpy(&result[i], new);
			i += ft_strlen(new);
			j += ft_strlen(old);
		}
		else
			result[i++] = s[j++];
	}
	result[i] = '\0';
	free(s);
	return (result);
}

t_exp	*ft_getidx(t_exp *exp, char *s)
{
	t_exp	*tmp;

	tmp = exp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(s)) == 0
			&& ft_strlen(s) == ft_strlen(tmp->var))
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

int	sk_ip(t_exp *tmp, char *s)
{
	int	k;

	k = 0;
	while (s[tmp->i] && ft_isvalid(s[tmp->i]))
	{
		tmp->i++;
		k++;
	}
	k++;
	return (k);
}
