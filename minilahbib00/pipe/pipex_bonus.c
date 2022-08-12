/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:12 by lsemlali          #+#    #+#             */
/*   Updated: 2022/08/07 21:36:31 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	mfrst_cmd(char **env, int *fd, char *cmd, int file1)
{
	char	**sp;
	char	*path;

	(void)file1;
	close(fd[0]);
	sp = ft_split(cmd, ' ');
	if (ft_strncmp(sp[0], "exit", 4) == 0 && ft_strlen(sp[0]) == 4)
		ft_exit(sp);
	path = get_path(handle_env(env), sp[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	ex_ecu(cmd, path, sp, env);
}

void	ex_comm(t_pipe p, int ac, char *av[], char *env[])
{
	int		i;
	int		k;

	k = 1;
	i = -1;
	while (++i < ac - 1)
	{
		next_cmd(env, &p, i, av[k++]);
		close(p.fd[i][0]);
		close(p.fd[i][1]);
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

void	child(t_pipe p, int ac, char *av[], char *env[])
{
	p.pid1 = fork();
	if (p.pid1 == 0)
		mfrst_cmd(env, p.fd[0], av[0], 0);
	else
	{
		p.cm++;
		ex_comm(p, ac, av, env);
		p.pid2 = fork();
		if (p.pid2 == 0)
			last_cmd(env, p.fd[ac - 1], av[ac], p.file2);
		f_close(p, ac);
		while (wait(NULL) != -1)
			;
	}
}

int	mpipex(int ac, char **av, char *env[])
{
	t_pipe	p;
	int		i;

	i = -1;
	p.fd = malloc(ac * sizeof(int *));
	while (++i < ac)
	{
		p.fd[i] = malloc(2 * sizeof(int));
		pipe(p.fd[i]);
	}
	child(p, ac, av, env);
	return (0);
}
