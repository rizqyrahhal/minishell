/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:10 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/09 21:04:52 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ex_ecu(char *path, char *sp[], t_envp *my_env)
{

//	fprintf(stderr, "----%s-----%s---\n", env[0], path);
	if (is_built(sp[0])) {
		__builtins(sp, my_env);
		exit (my_env->status);
	}
	else if (execve(path, sp, my_env->env) == -1)
	{
//		fprintf(stderr, "----s-----s---\n");
		put_error(sp[0], 1);
		if (sea_rch(sp[0], '/'))
			put_error(" : No such file or directory\n", 1);
		else
			put_error(" : Command not found\n", 1);
		exit (127);
	}
}

int all_len(t_command *cmd)
{
	int k;
	int i;

	i = 0;
	k = 0;
	while (cmd->cmd[i])
	{
		k += ft_strlen(cmd->cmd[i]);
		i++;
	}
	k += i - 1;
	return (k);
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
	//close(cmd->infile);
	//close(cmd->outfile);
	ex_ecu(path, cmd->cmd, my_env);
}

// echo -nnnn -nnnn skip all -nnn
// echo - prints
// export "=" -> segfault
void	one_cmd(t_envp *my_env, t_command *cmd)
{
	char	*path;
	int 	i;

	i = 0;
	printf("hello\n");
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
		cmd->cmd[0] = skip_sl(cmd->cmd[0]);
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
//		close(cmd->infile);
//		close(cmd->outfile);
		ex_ecu(path, cmd->cmd, my_env);
	}
}

void	last_cmd(t_envp *my_env, int *fd, t_command *cmd)
{
	char	*path;

	close(fd[1]);
	cmd->cmd[0] = skip_sl(cmd->cmd[0]);
	path = get_path(handle_env(my_env->env), cmd->cmd[0]);
	if (cmd->infile != 0)
		dup2(cmd->infile, 0);
	else
		dup2(fd[0], 0);
	//close(cmd->infile);
	close(fd[0]);
	if (cmd->outfile != 1)
		dup2(cmd->outfile, 1);
	//close(cmd->outfile);
	close(fd[1]);
	ex_ecu(path, cmd->cmd, my_env);
}
