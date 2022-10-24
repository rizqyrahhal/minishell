// print All data of linked list 
// void	print_node(t_command *lst, t_envp* my_env)
// {
// 	t_command*	list;
// 	int			i;

// 	if (lst == NULL)
// 		return;
// 	list = lst;
// 	(void)my_env;
// 	printf("\033[0;31m|--__---### All Data of Linked List Structre ###---__--|\033[0m\n");
// 	printf("pipe_numbere: %d\n", my_env->num_pipe);
// 	while (list != NULL)
// 	{
// 		printf("madir walo > %d\n", list->madir_walo);
// 		if (list->madir_walo == -404) {
// 			list = list->next;
// 		}
// 		else {
// 			i = 0;
// 			printf("COMMAND: ");
// 			while (list->cmd[i]) {
// 				printf("[%s]=%d  ", list->cmd[i], list->splite[i]);
// 				i++;
// 			}
// 			printf(", INfile: %d, OUTfile: %d", list->infile, list->outfile);
// 			printf("\n");
// 			list = list->next;
// 		}
// 	}
// }

// print token par token
// const char* token_type_to_str(int type)
// {
// 	if (type == TOKEN_STRING)
// 		return "TOKEN_STRING";
// 	else if (type == TOKEN_PIPE)
// 		return "TOKEN_PIPE";
// 	else if (type == TOKEN_IN)
// 		return "TOKEN_IN";
// 	else if (type == TOKEN_HERDOC)
// 		return "TOKEN_HERDOC";
// 	else if (type == TOKEN_OU)
// 		return "TOKEN_OU";
// 	else if (type == TOKEN_APPAND)
// 		return "TOKEN_APPAND";
// 	else if (type == TOKEN_EOF)
// 		return "TOKEN_EOF";
// 	else
// 		return "not_stringable";
// }

// char*	token_to_str(t_token* token)
// {
// 	const char* type_str;
// 	const char* template;
// 	char* str;

// 	type_str = token_type_to_str(token->e_type);
// 	template = "type = %s,	int_type = %d,	value = %s";
// 	str = ft_calloc(ft_strlen(type_str)
// 		+ ft_strlen(template) + 8, sizeof(char));
// 	sprintf(str, template, type_str, token->e_type, token->value);

// 	return str;
// }


// printf("\033[0;32m|---__LEXER__---###\033[0m %s \033[0;32m###---__LEXER__---|\033[0m\n", token_to_str(token));
// printf("\033[0;34m                     ---------------------\n                     | LINKED_LIST FINAL |\n                     ---------------------\n\033[0m");
// print_node(list, my_env);
// printf("------------------------------ FINISH -----------------------------------\n");