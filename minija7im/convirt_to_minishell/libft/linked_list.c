/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:12:19 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/26 23:40:44 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/struct.h"

t_command*	ft_lstlast(t_command* list)
{
	while (list)
	{
		if (!list->next)
			return(list);
		list = list->next;
	}
	return (list);
}

void	ft_addfront(t_command**	list, t_command *new)
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

t_command*	ft_lstnew(char** cmd_data, int infile, int outfile)
{
	t_command*	n1;

	n1 = malloc(sizeof(t_command));
	if (n1 == 0)
		return (NULL);
	if (cmd_data != NULL)
	{
		n1->cmd = (char**)malloc(sizeof(char*) * ft_d_strlen(cmd_data) + 1);
		n1->cmd = cmd_data;
	}
	n1->infile = infile;
	n1->outfile = outfile;
	n1->next = NULL;
	return (n1);
}