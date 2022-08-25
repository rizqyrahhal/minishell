/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:12:19 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 01:14:25 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/struct.h"

t_command*	ft_lstlast(t_command *list)
{
	while (list)
	{
		if (!list->next)
			return(list);
		list = list->next;
	}
	return (list);
}

void	ft_addfront(t_command	**list, t_command *new)
{
	t_command*	tmp;
	
	if (*list == NULL)
		*list = new;
	else
	{
		if (*list)
		{
			tmp = ft_lstlast(*list);
			tmp->next = new;
		}
		else
			*list = new;
	}
}

t_command	*ft_lstnew(char *s, int infile, int outfile)
{
	t_command*	n1;

	n1 = malloc(sizeof(t_command));
	if (n1 == 0)
		return (NULL);
	n1->cmd = malloc(ft_strlen(s));
	n1->cmd = s;
	n1->input = infile;
	n1->output = outfile;
	n1->next = NULL;
	return (n1);
}