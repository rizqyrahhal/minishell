/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/29 21:49:02 by rarahhal         ###   ########.fr       */
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

// void signal_ctrl_c(int sig)
// {
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// }

// void signal_ctrl_c_heredoc(int sig)
// {
// }

// void handle_signals(int sig)
// {
// 	if (sig == SIGINT)
// 		signal(SIGINT, signal_ctrl_c);
// 	else if (sig == SIGQUIT)
// 		signal(SIGQUIT, SIG_IGN);
// 	else if (sig == SIGHEREDOC)
// 		signal(SIGINT, signal_ctrl_c_heredoc);
// }

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

// char**	spli_ted(char* s)
// {
	
// }


void	printage(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("-- %s\n", arr[i]);
		i++;
	}
}

char**	fix_cmd(char** s, int *i)
{
	char**	str;
	char**	sp;
	int 	j;
	int 	k;
	int		z;

	j = 0;
	z = 0;
	k = *i + 1;
    sp = ft_split(s[*i], ' ');
    str = malloc((arr_size(s) + arr_size(sp)) * sizeof (char*));
	while (j < *i)
	{
		str[j] = s[j];
		j++;
	}
    while (sp[z])
    {
        str[j] = ft_strdup(sp[z]);
        j++;
		z++;
    }
	*i = j;
    while (s[k])
    {
		str[j] = ft_strdup(s[k]);
		k++;
        j++;
    }
    str[j] = NULL;
	free_arr(sp);
 	return (str);
 }

 void	check_list(t_command** list)
 {
	t_command*	tmp;
	int         i;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		i = 0;
		if (tmp->madir_walo == -404 || (ft_strncmp(tmp->cmd[0], "export", 6) == 0 && ft_strlen(tmp->cmd[0]) == 6))
			tmp = tmp->next;
		else
		{
			while (tmp->cmd[i]) {
				if (tmp->splite[i] == 1 && sea_rch(tmp->cmd[i], ' ')){
					tmp->cmd = fix_cmd(tmp->cmd, &i);
				}
				else
					i++;
			}
			tmp = tmp->next;
		}
	}
 }

/////////echo redirections in one_cmd
///////// SEGFAULT

//minishell > export var1=str
//minishell > echo $var1
//str
//		minishell > export var1+=$var
void	execution(t_command* list, t_envp* my_env)
{
	// int	k;

	handle_signals(SIGQUIT_INCHILD);
	// k = struct_size(list) - 1;
	// check_list(&list);
//	my_env->splite = 0;

	pipes(my_env->num_pipe, list, my_env);
//    free_arr(list->cmd);
	handle_signals(SIGQUIT);
}
