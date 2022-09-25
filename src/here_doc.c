/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/25 14:03:39 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_heredoc(int fd, char *delemeter, t_envp *my_env)
{
	char	*here_doc;

	here_doc = NULL;
	while (delemeter[0])
	{
		handle_signals(SIGHEREDOC);
		here_doc = readline("> ");
		if (!here_doc || !ft_strncmp(delemeter, here_doc,
				ft_strlen(delemeter) + 1))
			break ;
		here_doc = get_string(my_env, here_doc, 0);
		write(fd, here_doc, ft_strlen(here_doc));
		write(fd, "\n", 1);
		free(here_doc);
	}
	free(here_doc);
	exit (0);
}

int	creat_heredoc(int fd, char *delemeter, t_envp *my_env)
{
	pid_t	pid;
	int		st;

	pid = fork();
	if (pid == 0)
		open_heredoc(fd, delemeter, my_env);
	else
	{
		waitpid(pid, &st, 0);
		st = WEXITSTATUS(st);
		if (st == 1)
			return (-1);
	}
	close(fd);
	return (0);
}

t_heredoc	*init__(t_heredoc *here, char *src)
{
	here = malloc(sizeof(t_heredoc));
	here->lexer = init_lexer(src);
	here->lexer->not_expand = -1;
	here->i = 0;
	here->j = 0;
	here->str = malloc(1);
	here->str[0] = 0;
	return (here);
}

char	*here_doc(char *src, int stop, t_envp *my_env)
{
	t_heredoc	*here;

	here = malloc(sizeof(t_heredoc));
	here = init__(here, src);
	while (src && src[here->i] && here->i < stop)
	{
		if (src[here->i] == '<' && src[here->i + 1] == '<')
		{
			here = creat__file(here, src);
			here = get_delemeter(here, src);
			if (here->token->type == TOKEN_STRING)
				if (creat_heredoc(here->fd, here->token->value, my_env) == -1)
					return (NULL);
		}
		else
		{
			here->str = ft_d_realloc(here->str);
			here->str[here->j++] = src[here->i++];
			here->str[here->j] = '\0';
		}
	}
	here->str[here->j] = '\0';
	return (here->str);
}
