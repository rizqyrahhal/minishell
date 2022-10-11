/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/11 15:59:55 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

void	disable_ctlc(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	check_buf(char *buf, t_envp *my_env)
{
	if (g_sts->status == 1)
	{
		my_env->status = 1;
		g_sts->status = 0;
	}
	if (!buf)
	{
		free(buf);
		exit (my_env->status);
	}
}

void	minishell(t_envp *my_env)
{
	char	*buf;

	handle_signals(SIGINT);
	handle_signals(SIGQUIT);
	g_sts->status = 0;
	while (1)
	{
		buf = readline("m_shell>$ ");
		check_buf(buf, my_env);
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
	disable_ctlc();
	if (argc == 1)
		minishell(my_env);
	else
		printf("execute as follows: ./minishell (! whith no argument)\n");
	return (my_env->status);
}
