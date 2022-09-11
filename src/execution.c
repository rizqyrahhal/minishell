/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/11 20:27:29 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

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

char**	fix_cmd(char** s)
{
	char**	str;
	char**	sp;
	int 	i;

	i = 1;
	sp = ft_split(s[0], ' ');
	str = malloc((arr_size(s) + 2) * sizeof (char*));
	str[0] = ft_strdup(sp[0]);
	str[1] = ft_strdup(sp[1]);
	while (s[i])
	{
		str[i + 1] = ft_strdup(s[i]);
		i++;
	}
	str[i + 1] = NULL;

	return (str);
}

void	check_list(t_command** list)
{
	t_command*	tmp;

	tmp = *list;
	while (tmp)
	{
		if (sea_rch(tmp->cmd[0], ' ')) {
			tmp->cmd = fix_cmd(tmp->cmd);
		}
		// printf("--first    %s --\n", tmp->cmd[0]);
		tmp = tmp->next;
	}
}

void	execution(t_command* list, t_envp* my_env)
{
	int	k;

	k = struct_size(list) - 1;
	check_list(&list);
	pipes(k, list, my_env);
}
