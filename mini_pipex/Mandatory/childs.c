/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:19:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/05 17:18:27 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includs/pipex.h"

void	child_free(char **str, char *cmd)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	free(cmd);
}

char	*get_cmd(t_stock pipex)
{
	char	*tmp;
	char	*command;
	int		i;

	if (ft_strnstr(pipex.cmd_argemment[0], "/",
			ft_strlen(pipex.cmd_argemment[0])))
		return (pipex.cmd_argemment[0]);
	i = -1;
	while (pipex.cmd_paths[++i])
	{
		tmp = ft_strjoin("/", pipex.cmd_argemment[0]);
		command = ft_strjoin(pipex.cmd_paths[i], tmp);
		free(tmp);
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
	}
	return (NULL);
}

void	child_own(t_stock pipex, char *cmd, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		pipex.cmd_argemment = ft_split(cmd, ' ');
		pipex.cmd = get_cmd(pipex);
		if (!pipex.cmd)
		{
			cmd_not_found(pipex.cmd_argemment[0]);
			child_free(pipex.cmd_argemment, pipex.cmd);
			exit (EXIT_FAILURE);
		}
		
		if (execve(pipex.cmd, pipex.cmd_argemment, envp) == -1)
			return_error(pipex.cmd);
	}
	else
		waitpid(pid, NULL, 0);
}
