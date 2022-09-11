/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:12 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/11 18:06:27 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

int is_str(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

void	__builtins(char **sp, t_envp *my_env)
{
	if (ft_strncmp(sp[0], "cd", 2) == 0 && ft_strlen(sp[0]) == 2)
		ex_cd(sp, my_env);
	if (ft_strncmp(sp[0], "export", 6) == 0 && ft_strlen(sp[0]) == 6)
		ex_export(sp, my_env);
	if (ft_strncmp(sp[0], "env", 3) == 0 && ft_strlen(sp[0]) == 3)
		ex_env(sp, my_env);
	if (ft_strncmp(sp[0], "pwd", 3) == 0 && ft_strlen(sp[0]) == 3)
		ex_pwd(sp, my_env);
	if (ft_strncmp(sp[0], "unset", 5) == 0 && ft_strlen(sp[0]) == 5)
		ex_unset(sp, my_env);
	if (ft_strncmp(sp[0], "echo", 4) == 0 && ft_strlen(sp[0]) == 4)
		ex_echo(sp, my_env);
	if (ft_strncmp(sp[0], "exit", 4) == 0 && ft_strlen(sp[0]) == 4)
		ex_exit(sp, my_env);
}

void	ex_comm(t_pipe p, int k, t_command **cmd, t_envp *my_env)
{
	int	i;
	int	a;

	i = -1;
	a = 1;
	while (++i < k - 1)
	{		
		next_cmd(my_env, &p, i, *cmd);
		close(p.fd[i][0]);
		close(p.fd[i][1]);
		*cmd = (*cmd)->next;
	}
}

void	f_close(t_pipe p, int k)
{
	int	i;

	i = -1;
	while (++i < k)
	{
		close(p.fd[i][0]);
		close(p.fd[i][1]);
	}
}


void	multiple_p(t_pipe p, int k, t_command *cmd, t_envp *my_env)
{
	int st;
	p.pid1 = fork();
	if (p.pid1 == 0) {
		if (cmd->infile != -1) {
			frst_cmd(my_env, p.fd[0], cmd);
		}
	}
	else {
		ex_comm(p, k, &cmd->next, my_env);
		p.pid2 = fork();
		if (p.pid2 == 0)
			last_cmd(my_env, p.fd[k - 1], cmd->next);
		else {
			f_close(p, k);
			waitpid(p.pid2, &st, 0);
			while (wait(NULL) != -1);
			my_env->status = WEXITSTATUS(st);
		}
	}

}

int is_built(char *s)
{
	if (ft_strncmp(s, "cd", 2) == 0 && ft_strlen(s) == 2)
		return (1);
	if (ft_strncmp(s, "export", 6) == 0 && ft_strlen(s) == 6)
		return (1);
	if (ft_strncmp(s, "unset", 5) == 0 && ft_strlen(s) == 5)
		return (1);
	if (ft_strncmp(s, "env", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	if (ft_strncmp(s, "pwd", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	if (ft_strncmp(s, "echo", 4) == 0 && ft_strlen(s) == 4)
		return (1);
	if (ft_strncmp(s, "exit", 4) == 0 && ft_strlen(s) == 4)
		return (1);
	return (0);
}

void	child(t_pipe p, int k, t_command *cmd, t_envp *my_env)
{
	int status;
//	if (p.cm == 3)
//		k = ac - 6;
	if (k > 0)
		multiple_p(p, k, cmd, my_env);
	else
	{
		p.pid1 = fork();
		if (p.pid1 == 0) {
			if (!is_built(cmd->cmd[0]))
				one_cmd(my_env, cmd);
			else
				exit (0);
		}
		else {
			waitpid(p.pid1, &status, 0);
			my_env->status = WEXITSTATUS(status);
			__builtins(cmd->cmd, my_env);
		}
	}
}

int	pipes(int k, t_command *cmd, t_envp *my_env)
{
	t_pipe	p;
	int		i;

	i = -1;
	p.fd = malloc(k * sizeof(int *));
	while (++i < k)
	{
		p.fd[i] = malloc(2 * sizeof(int));
		pipe(p.fd[i]);
	}
	if (k < 0)
		return (0);
//	if (ft_strncmp(av[1], "here_doc\0", 9) == 0)
//		p.file1 = here_doc(av[2], &p, av[ac - 1]);
//	else
//	{
//	p.cm = 2;
//	}
//	if (p.file1 == -1)
//		put_error(ft_strjoin(av[1], " : No such file or directory\n"), 1);

	child(p, k, cmd, my_env);
	return (0);
}