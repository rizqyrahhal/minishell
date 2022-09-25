/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 01:12:19 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/25 14:00:57 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

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

char**	fill_t(char** s)
{
	int 	i;
	char**	str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc((ft_d_strlen(s) + 1) * sizeof(char*));
	while (s[i])
	{
		str[i] = ft_strdup(s[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

t_command*	ft_lstnew(char** cmd_data, int infile, int outfile)
{
	t_command*	n1;
	char**		s;

	s = fill_t(cmd_data);
	n1 = malloc(sizeof(t_command));
	if (n1 == 0)
		return (NULL);
	if (s != NULL)
	{
		n1->cmd = (char**)malloc(sizeof(char*) * ft_d_strlen(s) + 1);
		n1->cmd = s;
	}
	else
		n1->cmd = NULL;
	n1->infile = infile;
	n1->outfile = outfile;
	n1->next = NULL;
	return (n1);
}
