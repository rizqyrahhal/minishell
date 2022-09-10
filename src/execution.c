/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/10 14:44:03 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/execution.h"
int	sea_rrch(char *s, int a)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	ft_countt(char *s, int a)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == a)
			count++;
		i++;
	}
	return (count);
}

void free_arr(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}
//void signal_ctrl_c(int sig)
//{
//	rl_on_new_line();
//	rl_replace_line("", 0);
//}
//
//void signal_ctrl_c_heredoc(int sig)
//{
//}
//
//void handle_signals(int sig)
//{
//	if (sig == SIGINT)
//		signal(SIGINT, signal_ctrl_c);
//	else if (sig == SIGQUIT)
//		signal(SIGQUIT, SIG_IGN);
//	else if (sig == SIGHEREDOC)
//		signal(SIGINT, signal_ctrl_c_heredoc);
//}

int	struct_size(t_command *cmd)
{
	t_command	*tmp;
	int			k;

	k = 0;
	tmp = cmd;
	while (tmp)
	{
		k++;
		tmp = tmp->next;
	}
	return (k);
}

void	execution(t_command* list, t_envp* my_env)
{
	char		**s;
	int 		k, j;
	char		**sp;
	// t_envp		*my_env;
	char		*buf;

//	printf("----> cmd00 %s\n", list->cmd[0]);
	// my_env->PWD = getcwd(my_env->PWD, sizeof (my_env->PWD));
	k = struct_size(list) - 1;
	pipes(k, list, my_env);
}
