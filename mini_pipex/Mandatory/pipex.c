/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:42:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/05 17:21:10 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = -1;
	while (ft_strncmp("PATH", *envp, 4) != 0 && envp[++i])
		envp++;
	if (ft_strnstr(*envp, "PATH", 4))
		return (*envp + 5);
	else
		return ("PATH NOT EXISTE..");
}

int	pipex(int argc, char *cmd, char **envp)
{
	t_stock		pipex;

	pipex.env_path = find_path(envp);
	pipex.cmd_paths = ft_split(pipex.env_path, ':');
	child_own(pipex, cmd, envp);
	return (0);
}
