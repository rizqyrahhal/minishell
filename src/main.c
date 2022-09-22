/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/22 15:46:34 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*des cas non working
))) pwd if cd whit non option
*/


void signal_ctrl_c()
{
	write(2, "\n", 1);
	rl_on_new_line();
//	rl_replace_line("\0", 0);
	rl_redisplay();
}

// void signal_ctrl_c_heredoc()
// {
// 	r
// }


void	signal_ctrl_c_heredoc()
{
	exit(1);
}

void	signal_quit()
{
	printf("Quit: 3\n");
//	rl_replace_line("\0", 0);
}

void	signal_()
{
	printf("\n");
//	rl_replace_line("\0", 0);
}


void handle_signals(int sig)
{
	if (sig == SIGINT)
		signal(SIGINT, signal_ctrl_c);
 	else if (sig == SIGQUIT_INCHILD)
 		signal(3, signal_quit);
	 else if (sig == SIGINT_)
 		signal(SIGINT, signal_);
	 else if (sig == SIGQUIT)
 		signal(SIGQUIT, SIG_IGN);
	else if (sig == SIGHEREDOC)
	 	signal(SIGINT, signal_ctrl_c_heredoc);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*buf;
	t_envp	*my_env;

	(void)argv;
	my_env = (t_envp *)malloc(sizeof(t_envp));
	my_env->env = (char **)malloc(sizeof(char *) * (ft_d_strlen(env) + 1));
	fill_env(env, my_env);
	my_env->PWD = getcwd(NULL, 0);
	my_env->status = 0;
	if (argc == 1)
	{
		while (1)
		{
			handle_signals(SIGINT);
			handle_signals(SIGQUIT);
			buf = readline("\033[0;33mminishell > \033[0m");
			handle_signals(SIGINT_);
			if (!buf)
				exit (0);
			add_history(buf);
			if (buf)
				tac_compile(buf, my_env);
			free(buf);
		}
	}
	else
		printf("execute as fallows: ./minishell (! whilt no argement)\n");
	return (0);
}
