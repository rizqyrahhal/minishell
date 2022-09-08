/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/20 10:34:45 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"
#include "readline/history.h"
#include <string.h>
#include <ctype.h>

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

int	main(int ac, char *av[], char *env[])
{
	t_command*	command;
	char		**s;
	int 		k, j;
	char		**sp;
	t_envp		*my_env;
	char		*buf;


	(void)ac;
	(void)av;

	my_env = malloc(sizeof(my_env));
	my_env->env = malloc((arr_size(env) + 1) * sizeof(char *));
	fill_env(env, my_env);
	k = arr_s(my_env->env, "PWD");
	my_env->PWD = ft_substr(my_env->env[k], 4, ft_strlen(my_env->env[k]) - 4);
	while (1) {

		command = malloc(sizeof(t_command));
		command = NULL;
		j = 0;
		yellow();
		buf = readline("minibash -> ");
		reset();
		if (!buf)
			break ;
		sp = ft_split(buf, '|');
		j = 0;
		k = 0;
		while (sp[j]) {
			s = ft_split(sp[j], ' ');
			k = 0;
			command = get_data(command, s, 0, 1);
			while (s[k])
			{
				free(s[k]);
				k++;
			}
			free(s[k]);
			free(s);
			j++;
		}
		k = arr_size(sp) - 1;
		if (k < 0)
			continue ;
		pipes(k, command, my_env);
		printf("%d\n", r);
		j = 0;
		while (command->cmd[j])
		{
			free(command->cmd[j]);
			j++;
		}
		free(command->cmd[j]);
		free(command);
		j = 0;
		while (sp[j])
		{
			free(sp[j]);
			j++;
		}
		free(sp[j]);
		free(sp);
		free(buf);
	}
	// mkdir a > rm -rf ../a > cd . "you should print error message and join the 'bla/bla/a/.'"
	return (0);
}
