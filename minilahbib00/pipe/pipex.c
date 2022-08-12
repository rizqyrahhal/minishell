/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:04 by lsemlali          #+#    #+#             */
/*   Updated: 2022/08/07 21:19:13 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_s(t_pipe p, char *av, char *env[])
{
	p.pid1 = fork();
	if (p.pid1 == -1)
		put_error("Error in fork\n", 0);
	if (p.pid1 == 0)
	{
		if (p.file1 != -1)
			frst_cmd(env, av, p.file1);
	}
	else
	{
		wait(NULL);
	}
}

int	pipex(int ac, char *av, char *env[])
{
	t_pipe	p;

	child_s(p, av, env);
	return (0);
}

void	dchild_s(t_pipe p, int *fd, char *av[], char *env[])
{
	p.pid1 = fork();
	if (p.pid1 == -1)
		put_error("Error in fork\n", 0);
	if (p.pid1 == 0)
		dfrst_cmd(env, fd, av[0], p.file1);
	else
	{
		p.pid2 = fork();
		if (p.pid2 == -1)
			put_error("Error in fork\n", 0);
		if (p.pid2 == 0)
			last_cmd(env, fd, av[1], p.file2);
		close(fd[0]);
		close(fd[1]);
		while (wait(NULL) != -1)
		{
		}
	}
}

int	dpipex(int ac, char *av[], char *env[])
{
	t_pipe	p;
	int		fd[2];

	pipe(fd);
	dchild_s(p, fd, av, env);
	return (0);
}