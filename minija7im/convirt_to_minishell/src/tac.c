/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/30 21:30:55 by rarahhal         ###   ########.fr       */
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

	if (lst == NULL)
		return;
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

void	free_list(t_command* list)
{
	int	i;

	i = 0;
	while (list->cmd[i]){
		free(list->cmd[i]);
		i++;
	}
	free(list->cmd);
	free(list);
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
		// printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
		list = parser(lexer, token, list);
		token = lexer_next_token(lexer);
	}

	// lexer freeeeee
	free(lexer); /// i7timal ykon more leaks fi ldakhal
	free(token); //// i7timal ykon more leaks in insind

/* LEAKS  : 7ata n7ayd lprantage wo les function dyalo 3ad nchof m3ah */

	// printf("LOGNEM=%s\n", getenv("LOGNAME"));
	// execution part HERE!!
	printf("\033[0;34m                     ---------------------\n                     | LINKED_LIST FINAL |\n                     ---------------------\n\033[0m");
	print_node(list);
	if (list)
		free_list(list);    // ndya khss nrja3 m3a lcod wo nfrii li khas ytfriya ms 7ata ntchiki readline achman lik filha
}

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::SEGNAL:::::::::::::::::::::::::::::::::::::;:::::::::::::::::::::::::::::::::::::::
1) ay while katssana input khas ykono fiha les function li kayhandliw segnal aw l funcion le ktcheke segnal (lmohim chi 7aja b7al haka ):::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/