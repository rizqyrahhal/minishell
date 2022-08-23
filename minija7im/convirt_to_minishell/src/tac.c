/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/23 16:17:28 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tac.h"
#include "../includes/lexer.h"
#include <stdlib.h>

void	ft_addfront(t_command	*list, t_command *new)
{
	list->next = new;
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

void	check_struct(t_command **list)
{
	int	i;

	i = 0;
	while (list[i]->next != NULL)
	{
		printf("COMMAND: %s, INfile: %d, OUTfile: %d\n", list[i]->cmd, list[i]->input, list[i]->output);
	}
}

void	tac_compile(char* src)
{
	t_lexer*	lexer;
	t_token*	token;
	t_command*	list;
	t_command*	new;
	int			i = 0;

	lexer = init_lexer(src);
	token = lexer_next_token(lexer);
	// list1 = (t_command*)malloc(sizeof(t_command));
	// list1->cmd = (char**)malloc(2);
	while(token->type != TOKEN_EOF)
	{
		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
		if (token->type == TOKEN_STRING && i == 0)
		{	
			list = ft_lstnew(token->value, 0, 1);
			printf("COMMAND: %s\nINfile: %d\nOUTfile: %d\n", list->cmd, list->input, list->output);
			// i++;
		}
		if (token->type == TOKEN_PIPE)
		{
			ft_addfront(list, new);
			new = ft_lstnew(token->value, 0, 1);
			printf("COMMAND: %s\nINfile: %d\nOUTfile: %d\n", new->cmd, new->input, new->output);
		}
		token = lexer_next_token(lexer);
	}
	// check_struct(new);
}
