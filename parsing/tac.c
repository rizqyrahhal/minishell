/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tac.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:05 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 19:29:51 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_list(t_command *list)
{
	t_command	*new;
	int			i;

	while (list)
	{
		i = 0;
		while (list && list->madir_walo == 0 && list->cmd[i])
		{
			free(list->cmd[i]);
			i++;
		}
		free(list->cmd);
		new = list;
		list = list->next;
		free(new);
	}
}

void	merging_work(t_envp *my_env, char *src)
{
	t_lexer		*lexer;
	t_token		*token;
	t_command	*list;

	lexer = init_lexer(src);
	lexer->not_expand = 0;
	lexer_skip_whitespace(lexer);
	lexer->my_env = my_env;
	token = lexer_next_token(lexer);
	list = NULL;
	while (token->e_type != TOKEN_EOF)
	{
		list = parser(lexer, token, list);
		token = lexer_next_token(lexer);
	}
	_tac_free(&lexer, &token, src);
	if (list)
	{
		execution(list, my_env);
		my_env->num_pipe = 0;
		free_list(list);
	}
}

void	tac_compile(char *src, t_envp *my_env)
{
	int	i;

	i = 0;
	if (check_syntax_error(src, &i) == -1)
	{
		my_env->status = 258;
		src = here_doc(src, i, my_env);
		free(src);
		return ;
	}
	else
		src = here_doc(src, ft_strlen(src), my_env);
	if (!src)
		return ;
	merging_work(my_env, src);
}
