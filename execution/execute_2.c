/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:31 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/28 22:10:39 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

void	f_close(t_pipe *p, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		close(p->fd[i][0]);
		close(p->fd[i][1]);
		i++;
	}
}

int	is_built(char *s)
{
	if (ft_strncmp(s, "cd", 2) == 0 && ft_strlen(s) == 2)
		return (1);
	if (ft_strncmp(s, "export", 6) == 0 && ft_strlen(s) == 6)
		return (1);
	if (ft_strncmp(s, "unset", 5) == 0 && ft_strlen(s) == 5)
		return (1);
	if (ft_strncmp(lo_wer(s), "env", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	if (ft_strncmp(lo_wer(s), "pwd", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	if (ft_strncmp(lo_wer(s), "echo", 4) == 0 && ft_strlen(s) == 4)
		return (1);
	if (ft_strncmp(s, "exit", 4) == 0 && ft_strlen(s) == 4)
		return (1);
	return (0);
}

void	__builtins(char **sp, t_envp *my_env, int out, int k)
{
	char	*s;

	s = lo_wer(sp[0]);
	if (ft_strncmp(sp[0], "cd", 2) == 0 && ft_strlen(sp[0]) == 2)
		ex_cd(sp, my_env);
	if (ft_strncmp(sp[0], "export", 6) == 0 && ft_strlen(sp[0]) == 6)
		ex_export(sp, my_env, out);
	if (ft_strncmp(s, "env", 3) == 0 && ft_strlen(sp[0]) == 3)
		ex_env(sp, my_env, out);
	if (ft_strncmp(s, "pwd", 3) == 0 && ft_strlen(sp[0]) == 3)
		ex_pwd(sp, my_env, out);
	if (ft_strncmp(sp[0], "unset", 5) == 0 && ft_strlen(sp[0]) == 5)
		ex_unset(sp, my_env);
	if (ft_strncmp(s, "echo", 4) == 0 && ft_strlen(sp[0]) == 4)
		ex_echo(sp, my_env, out);
	if (ft_strncmp(sp[0], "exit", 4) == 0 && ft_strlen(sp[0]) == 4)
		ex_exit(sp, my_env, k);
	free(s);
}
