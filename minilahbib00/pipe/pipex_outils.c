/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:10 by lsemlali          #+#    #+#             */
/*   Updated: 2022/08/07 16:46:47 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dfrst_cmd(char **env, int *fd, char *cmd, int file1)
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
