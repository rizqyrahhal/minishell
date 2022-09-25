/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:01:02 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 14:19:42 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*skip_sl(char	*cmd)
{
	char	*n_cmd;
	int		i;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		if (cmd[i] == '/')
			break ;
		i--;
	}
	n_cmd = ft_substr(cmd, i + 1, ft_strlen(cmd) - (i + 1));
	return (n_cmd);
}

char	*get_path(char *s, char *cmd)
{
	char	**sp;
	char	*tmp;
	char	*n_cmd;
	int		i;

	if (!s)
		return (NULL);
	sp = ft_split(s, ':');
	i = -1;
	if (sea_rch(cmd, '/'))
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	while (sp[++i])
	{
		n_cmd = ft_strjoin(sp[i], tmp);
		if (!access(n_cmd, F_OK) && !access(n_cmd, X_OK))
			return (n_cmd);
		n_cmd = NULL;
	}
	free_arr(sp);
	free(tmp);
	free(s);
	if (n_cmd == NULL && access(cmd, X_OK) == 0)
		return (cmd);
	return (0);
}

char	*handle_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", ft_substr(env[i], 0, 4), 4) == 0)
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		i++;
	}
	return (NULL);
}
