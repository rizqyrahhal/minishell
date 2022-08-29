/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/29 19:16:19 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tac.h"
#include "../includes/lexer.h"
#include "../include/struct.h"
#include <stdlib.h>

// print All data of linked list 
void	print_node(t_command *lst)
{
	t_command*	list;
	int			i;

	list = lst;
	printf("\033[0;31m|--__---### All Data of Linked List Structre ###---__--|\033[0m\n");
	while (list != NULL)
	{
		i = 0;
		printf("COMMAND: ");
		while (list->cmd[i])
		{
			printf("%s ", list->cmd[i]);
			i++;
		}
		printf(", INfile: %d, OUTfile: %d\n", list->infile, list->outfile);
		list = list->next;
	}

}

void	tac_compile(char* src)
{
	t_lexer*	lexer;
	t_token*	token;
	t_command*	list;

	// function  pour check les error comme an while lope in src character par chararcter   (here or in main Function)
	// static int	error_befor_parser(char* src);  (function roturn exite status)
	lexer = init_lexer(src);
	token = lexer_next_token(lexer);
	list = (t_command*)malloc(sizeof(t_command));
	list = NULL;
	while(token->type != TOKEN_EOF)
	{
		printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
		list = parser(lexer, token, list);
		token = lexer_next_token(lexer);
	}
	// printf("LOGNEM=%s\n", getenv("LOGNAME"));
	// execution part HERE!!
	printf("\033[0;34m                     ---------------------\n                     | LINKED_LIST FINAL |\n                     ---------------------\n\033[0m");
	print_node(list);
	free(list);
}
