/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/09 21:09:09 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    *ft_cpy(char *s, int k); //move to hedr

void	fill_env(char *env[], t_envp *my_env)
{
	int i;

	i = 0;
	while (env[i])
	{
		my_env->env[i] = ft_cpy(env[i], ft_strlen(env[i]));
		i++;
	}
	my_env->env[i] = 0;
}


void	print_a(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

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
}

t_command*	get_data(t_command* command, char** cmd, int infile, int outfile)
{
	t_command	*tmp;

//	command->cmd = malloc((ft_d_strlen(cmd) + 1) * sizeof(char*));
	tmp = ft_lstnew(cmd, infile, outfile);

	ft_addfront(&command, tmp);

	return (command);
}

void red () {
	printf("\033[1;31m");
}

void yellow() {
		printf("\033[1;33m");
}

void reset () {
	printf("\033[0m");
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

void	execution(t_command* list, t_envp* my_env)
{
	char		**s;
	int 		k, j;
	char		**sp;
	// t_envp		*my_env;
	char		*buf;

	k = arr_s(my_env->env, "PWD");
	my_env->PWD = getcwd(my_env->PWD, sizeof (my_env->PWD));
	
	pipes(k, list, my_env);
}
