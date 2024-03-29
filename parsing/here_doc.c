/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 23:01:49 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_heredoc(int fd, char *delemeter, t_envp *my_env)
{
	char	*here_doc;

	here_doc = NULL;
	while (1)
	{
		handle_signals(SIGHEREDOC);
		here_doc = readline("> ");
		if (!here_doc || !ft_strncmp(delemeter, here_doc,
				ft_strlen(delemeter) + 1))
		{
			if (!here_doc && g_sts->status != 1)
				g_sts->ginp = SIGHEREDOC;
			break ;
		}
		here_doc = get_string(my_env, here_doc, 0);
		write(fd, here_doc, ft_strlen(here_doc));
		write(fd, "\n", 1);
		free(here_doc);
	}
	free(here_doc);
}

int	creat_heredoc(int fd, char *delemeter, t_envp *my_env, t_heredoc **here)
{
	if ((*here)->token->e_type == TOKEN_STRING)
	{
		g_sts->status = 0;
		open_heredoc(fd, delemeter, my_env);
		if (g_sts->status == 1)
		{
			dup2(g_sts->ginp, 0);
			my_env->status = g_sts->status;
			_tokenfree_(&*here);
			return (-1);
		}
		close(fd);
	}
	return (0);
}

t_heredoc	*init__(char *src)
{
	t_heredoc	*here;

	here = malloc(sizeof(t_heredoc));
	here->lexer = init_lexer(src);
	here->lexer->not_expand = -1;
	here->token = init_token(NULL, 0);
	here->i = 0;
	here->j = 0;
	here->str = malloc(1);
	here->str[0] = 0;
	return (here);
}

t_heredoc	*skip_qouting(t_heredoc *here, char *src)
{
	if (src[here->i] == '"')
	{
		here->str = ft_d_realloc(here->str);
		here->str[here->j++] = src[here->i++];
		here->str[here->j] = '\0';
		while (src[here->i] != '"')
		{
			here->str = ft_d_realloc(here->str);
			here->str[here->j++] = src[here->i++];
			here->str[here->j] = '\0';
		}
	}
	if (src[here->i] == '\'')
	{
		here->str = ft_d_realloc(here->str);
		here->str[here->j++] = src[here->i++];
		here->str[here->j] = '\0';
		while (src[here->i] != '\'')
		{
			here->str = ft_d_realloc(here->str);
			here->str[here->j++] = src[here->i++];
			here->str[here->j] = '\0';
		}
	}
	return (here);
}

char	*here_doc(char *src, int stop, t_envp *my_env)
{
	t_heredoc	*here;

	here = NULL;
	here = init__(src);
	while (src && src[here->i] && here->i < stop)
	{
		here = skip_qouting(here, src);
		if (src[here->i] == '<' && src[here->i + 1] == '<')
		{
			here = creat__file(here, src, stop);
			if (!here)
				return (NULL);
			if (creat_heredoc(here->fd, here->token->value,
					my_env, &here) == -1)
				return (NULL);
		}
		else
		{
			here->str = ft_d_realloc(here->str);
			here->str[here->j++] = src[here->i++];
			here->str[here->j] = '\0';
		}
	}
	return (_free_token(here, src));
}

// int	creat_heredoc(int fd, char *delemeter, t_envp *my_env, t_heredoc **here)
// {
// 	pid_t	pid;
// 	int		st;

// 	if ((*here)->token->e_type == TOKEN_STRING)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 			open_heredoc(fd, delemeter, my_env);
// 		else
// 		{
// 			waitpid(pid, &st, 0);
// 			st = WEXITSTATUS(st);
// 			if (st == 1)
// 			{
// 				_tokenfree_(&*here);
// 				return (-1);
// 			}
// 		}
// 		close(fd);
// 	}
// 	return (0);
// }