/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:42:43 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/30 11:42:44 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

t_exp	*lst_last(t_exp *list)
{
	while (list)
	{
		if (!list->next)
			return (list);
		list = list->next;
	}
	return (list);
}

void	add_front(t_exp **list, t_exp *new)
{
	t_exp	*tmp;

	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		if (*list)
		{
			tmp = lst_last(*list);
			tmp->next = new;
		}
		else
			*list = new;
	}
}

t_exp	*ft_getvar(char *env[], t_exp *exp)
{
	int		i;
	int		j;
	char	*str;
	t_exp	*tmp;

	j = 0;
	i = 0;
	while (env[i])
	{
		tmp = malloc(sizeof (t_exp));
		while (env[i][j] != '=')
			j++;
		str = ft_cpy(env[i], j++);
		tmp->var = ft_strjoin("$", str);
		tmp->value = ft_cpy(&env[i][j], ft_strlen(&env[i][j]));
		add_front(&exp, tmp);
		j = 0;
		i++;
		tmp = NULL;
		free(str);
	}
	return (exp);
}

int	ft_isvalid(int c)
{
	if ((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}
