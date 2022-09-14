/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/13 18:05:12 by rarahhal         ###   ########.fr       */
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

//char**	spli_ted(char* s)
//{
//
//}

//char**	fix_cmd(char** s)
//{
//	char**	str;
//	char**	sp;
//	int 	i;
//	int 	j;
//
//	i = 0;
//	j = 0;
//    str =
//	while (s[i])
//	{
//		j = 0;
//		if (sea_rch(s[i], ' '))
//			sp = spli_ted(s[i]);
//		while (sp[j])
//		{
//
//		}
//		// sp = ft_split(s[i], ' ');
//		// str = malloc((arr_size(s) + 2) * sizeof (char*));
//		// while (sp[i])
//		// {
//		// 	str[i] = ft_strdup(sp[i]);
//		// 	i++;
//		// }
//		// j = 1;
//		// while (s[j])
//		// {
//		// 	str[i] = ft_strdup(s[j]);
//		// 	i++;
//		// 	j++;
//		// }
//		// str[i] = NULL;
//	}
//
//	return (str);
//}

//void	check_list(t_command** list, t_envp* my_env)
//{
//	t_command*	tmp;
//
//	tmp = *list;
//	while (tmp)
//	{
//		if (my_env->splite == -404) {
//			tmp->cmd = fix_cmd(tmp->cmd);
//		}
//		// if (sea_rch(tmp->cmd[0], ' ')) {
//		// 	tmp->cmd = fix_cmd(tmp->cmd);
//		// }
//		// printf("--first    %s --\n", tmp->cmd[0]);
//		tmp = tmp->next;
//	}
//}

/////////echo redirections in one_cmd
///////// SEGFAULT

void	execution(t_command* list, t_envp* my_env)
{
	int	k;
    (void)list;
    (void)my_env;
	k = struct_size(list) - 1;
//	check_list(&list, my_env);
//	my_env->splite = 0;
	pipes(k, list, my_env);
}
