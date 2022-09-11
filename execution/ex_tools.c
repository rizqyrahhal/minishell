/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:10 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/11 18:06:13 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	ex_ecu(char *path, char *sp[], t_envp *my_env)
{
	if (is_built(sp[0])) {
		__builtins(sp, my_env);
		exit (my_env->status);
	}
	else if (execve(path, sp, my_env->env) == -1)
	{
		if (sea_rch(sp[0], '/'))
		{
			write(2, "minishell: ", 11);
			write(2, sp[0], ft_strlen(sp[0]));
			write(2, ": No such file or directory\n", 28);
		// printf("minishell: %s: No such file or directory\n", sp[0]);
		}
		else
		{
			write(2, "minishell: ", 11);
			write(2, sp[0], ft_strlen(sp[0]));
			write(2, ": Command not found\n", 20);
			// printf("minishell: %s: Command not found\n", sp[0]);
		}
		exit (127);
	}
}

void	frst_cmd(t_envp *my_env, int *fd, t_command *cmd)
{
	char	*path;

	close(fd[0]);
		path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
		dup2(cmd->infile, 0);
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	else
		dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	ex_ecu(path, cmd->cmd, my_env);
}

void	one_cmd(t_envp *my_env, t_command *cmd)
{
	char	*path;

	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0) {
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile != 1) {
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	ex_ecu(path, cmd->cmd, my_env);
}

void	next_cmd(t_envp *my_env, t_pipe *p, int i, t_command *cmd)
{
	char	*path;

	(*p).id[i] = fork();
	if ((*p).id[i] == 0)
	{
		close((*p).fd[i + 1][0]);
		close((*p).fd[i][1]);
		path = get_path(handle_env(my_env->env), cmd->cmd[0]);
		if (cmd->infile != 0)
			dup2(cmd->infile, 0);
		else
			dup2((*p).fd[i][0], 0);
		if (cmd->outfile != 1)
			dup2(cmd->outfile, 1);
		else
			dup2((*p).fd[i + 1][1], 1);
		close((*p).fd[i][0]);
		close((*p).fd[i][1]);
		close((*p).fd[i + 1][0]);
		close((*p).fd[i + 1][1]);
		ex_ecu(path, cmd->cmd, my_env);
	}
}

void	last_cmd(t_envp *my_env, int *fd, t_command *cmd)
{
	char	*path;

	close(fd[1]);
	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
		dup2(cmd->infile, 0);
	else
		dup2(fd[0], 0);
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	close(fd[0]);
	close(fd[1]);
	ex_ecu(path, cmd->cmd, my_env);
}
