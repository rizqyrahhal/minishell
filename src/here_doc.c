/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/24 17:33:15 by rarahhal         ###   ########.fr       */
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
		if (!here_doc || !ft_strncmp(delemeter, here_doc, ft_strlen(delemeter) + 1))
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

// int	creat__file(char *src, int *i, char *str, int *j)
// {
// 	char	*del_to_name;
// 	int		k;
// 	int		fd;
// 	int 	a;
// 	int		b;

// 	a = *i;
// 	b = *j;
// 	del_to_name = ft_randstring(8);
// 	fd = open(del_to_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	str = ft_d_realloc(str);
// 	str = ft_d_realloc(str);
// 	printf("---------%d---------------\n", (*i));
// 	str[b++] = src[a++];
// 	str[b++] = src[a++];
// 	str[b] = '\0';
// 	while ((src[a] == ' ' || src[a] == '\t') && src[a]){
// 		str = ft_d_realloc(str);
// 		str[b++] = src[a++];
// 		str[b] = '\0';
// 	}
// 	k = 0;
// 	while (del_to_name && del_to_name[k])
// 	{
// 		str = ft_d_realloc(str);
// 		str[b++] = del_to_name[k++];
// 		str[b] = '\0';
// 	}
// 	*i = a;
// 	*j = b;
// 	return (fd);
// }





char	*here_doc(char *src, int stop, t_envp *my_env)
{
	int		i;
	char*	str;
	int		j;
	char*	del_to_name;
	int		k;
	int		fd;

	t_lexer *lexer;
	t_token *token;
	lexer = init_lexer(src);
	lexer->not_expand = -1;
	i = 0;
	j = 0;
	str = malloc(1);
	str[0] = 0;
	while(src && src[i] && i < stop)
	{
		k = 0;
		if (src[i] == '<' && src[i + 1] == '<')
		{
			// fd = creat__file(src, &i, str, &j);
			del_to_name = ft_randstring(8);
			fd = open(del_to_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
			
			str = ft_d_realloc(str);
			str = ft_d_realloc(str);
			str[j++] = src[i++];
			str[j++] = src[i++];			
			str[j] = '\0';
			while (src[i] && (src[i] == ' ' || src[i] == '\t')){
				str = ft_d_realloc(str);
				str[j++] = src[i++];
				str[j] = '\0';
			}

			while (del_to_name && del_to_name[k])
			{
				str = ft_d_realloc(str);
				str[j++] = del_to_name[k++];
				str[j] = '\0';
			}
			// printf("src after change : %s\n size_src %zu\n i: %d\n", src, ft_strlen(src), i);
			
			// printf("str after change : %s\n size_str %zu\n j: %d\n", str, ft_strlen(str), j);

			while ((int)lexer->i <= i)
				token = lexer_next_token(lexer);

			while (src[i] && (src[i] != ' ' && src[i] != '\t' && src[i] != '>' && src[i] != '<' && src[i] != '|'))
				i++;
			if (creat_heredoc(fd, token->value, my_env) == -1)
				return (NULL);
		}
		else
		{
			str = ft_d_realloc(str);
			str[j++] = src[i++];
			str[j] = '\0';
		}
	}
	str[j] = '\0';
	return (str);
}