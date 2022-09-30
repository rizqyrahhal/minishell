/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/30 18:28:35 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*des cas non working
))) pwd if cd whit non option
))) << l 'wfwfwfwfwe << l       segmentetion fault par fois   hadchi y9dar ykon andi
))) export a="-l   -a"     and ls $a      errrooor par fois freeed
))) ls << "<<"
))) ls <<l | cat
*/

void signal_ctrl_c()
{
	write(2, "\n", 1);
	rl_on_new_line();
	// rl_replace_line("\0", 0);
	rl_redisplay();
}

void	signal_ctrl_c_heredoc()
{
	exit(1);
}

void	signal_quit()
{
	printf("Quit: 3\n");
	// rl_replace_line("\0", 0);
}

void	signal_()
{
	printf("\n");
	// rl_replace_line("\0", 0);
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
	fill_env(env, my_env);
	my_env->pwd = getcwd(NULL, 0);
	my_env->status = 0;
	my_env->num_pipe = 0;
	if (argc == 1)
	{
		while (1)
		{
			handle_signals(SIGINT);
			handle_signals(SIGQUIT);
			buf = readline("\033[0;33mminishell > \033[0m");
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
			handle_signals(SIGINT_);
			add_history(buf);
			if (buf)
				tac_compile(buf, my_env);
			free(buf);
//			system("leaks minishell");
		}
	}
	else
		printf("execute as fallows: ./minishell (! whilt no argement)\n");
	return (my_env->status);
}

// export MallocStackLogging=1