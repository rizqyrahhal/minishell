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

int	main(int ac, char *av[], char *env[])
{
	t_command*	command;
	t_exp *exp;
	char		**s;
	char		**sp;
	int 		k, j;
	t_envp		*my_env;

	exp = malloc((arr_size(env) + 1) * sizeof (t_exp));
	ft_getVar(env, &exp);
	my_env = malloc(sizeof (my_env));
	my_env->env = malloc((arr_size(env) + 1) * sizeof (char*));
	fill_env(env, my_env);

//	k = open("makefile", O_RDONLY);
//	j = open("heaven", O_RDWR | O_CREAT | O_TRUNC, 0600);
	command = malloc(sizeof (t_command));
	command = NULL;
	s = malloc(4 * sizeof(char*));
	j = 1;
	while (j < ac) {
		s = ft_split(av[j], ' ');
		printf("%s\n", s[0]);
		s[1] = ft_exp(s[1], exp, my_env->env);
		//s[2] = ft_exp(s[2], exp, my_env->env);
		//s[3] = ft_exp(s[3], exp, my_env->env);
		command = get_data(command, s, 0, 1);
		j++;
	}
	k = ac - 2;
//	s[0] = ft_strdup("cat");
//	s[1] = ft_strdup("-e");
//	s[2] = NULL;
//	command = get_data(s, 0, 1);]
//	int z = 0;
//
//	while (command)
//	{
//		command = command->next;
//	}
	t_command *nn;

	nn = command;
	pipes(k, command, my_env);
	printf("%d\n", r);
//	printf("---%d\n", command->status);
//	pipes(0, nn->next, my_env);
//	print_arr(my_env->export);
	//print_a(my_env->env);
//	print_arr(my_env->env);

	//exp = malloc(sizeof(t_exp) * env_size(env));
    //ft_getVar(env, &exp);
//	while(1)
//	{
		//buf = readline("\033[0;33m minishell > \033[0m");
		//if (buf[0] == 0)
			//continue ;
        //add_history(buf);
        //buf = ft_exp(buf, exp, env);
		//k = ft_countt(buf, '|');
		//command->cmd = ft_split(buf, '|');
//		free(buf);
//	}
	return (0);
}
