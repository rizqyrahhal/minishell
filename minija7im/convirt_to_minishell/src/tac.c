/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/23 18:08:49 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tac.h"
#include "../includes/lexer.h"
#include <stdlib.h>

void	ft_addfront(t_command	**list, int i, t_command *new)
{
	list[i]->next = new;
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

// print All data of linked list 
void	print_node(t_command **list)
{
	int	i;

	i = 0;
	printf("\033[0;31m|--__---### All Data of Linked List Structre ###---__--|\033[0m\n");
	while (list)
	{
		printf("COMMAND: %s, INfile: %d, OUTfile: %d\n", list[i]->cmd, list[i]->input, list[i]->output);
		if (list[i]->next == NULL)
			break;
		i++;
	}
}

void	tac_compile(char* src)
{
	t_lexer*	lexer;
	t_token*	token;
	t_command**	list;
	t_command*	new;
	int			i = 0;

	lexer = init_lexer(src);
	token = lexer_next_token(lexer);
	list = (t_command**)malloc(sizeof(t_command*));
	while(token->type != TOKEN_EOF)
	{
		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
		if (token->type == TOKEN_STRING)
		{	
			list[i] = ft_lstnew(token->value, 0, 1);
			printf("COMMAND: %s\nINfile: %d\nOUTfile: %d\n", list[i]->cmd, list[i]->input, list[i]->output);
		}
		if (token->type == TOKEN_PIPE)
		{
			printf("___-- IN condition PIPE --___\n");
			ft_addfront(list, i, new);
			i++;
			list[i] = ft_lstnew(token->value, 0, 1);
			printf("COMMAND: %s\nINfile: %d\nOUTfile: %d\n", list[i]->cmd, list[i]->input, list[i]->output);
		}
		token = lexer_next_token(lexer);
	}
	print_node(list);
}
