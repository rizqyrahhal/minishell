/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/04 15:53:52 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minishell(t_envp *my_env)
{
	char	*buf;

	while (1)
	{
		handle_signals(SIGINT);
		handle_signals(SIGQUIT);
		buf = readline("m_shell>$ ");
		if (!buf)
		{
			free(buf);
			exit (my_env->status);
		}
		if (!buf[0])
		{
			free(buf);
			continue ;
		}
		else
			g_sts->ginp = -1;
		handle_signals(SIGINT_);
		add_history(buf);
		if (buf)
			tac_compile(buf, my_env);
		free(buf);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_envp	*my_env;

	(void)argv;
	my_env = (t_envp *)malloc(sizeof(t_envp));
	g_sts = malloc(sizeof(t_status));
	g_sts->ginp = -1;
	fill_env(env, my_env);
	my_env->pwd = getcwd(NULL, 0);
	my_env->status = 0;
	my_env->num_pipe = 0;
	if (argc == 1)
		minishell(my_env);
	else
		printf("execute as follows: ./minishell (! whith no argument)\n");
	return (my_env->status);
}
