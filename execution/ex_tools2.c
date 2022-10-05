/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_tools2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:25 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/05 16:32:41 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*get_path(char *s, char *cmd)
{
	char	**sp;
	char	*tmp;
	char	*n_cmd;
	int		i;

	if (sea_rch(cmd, '/'))
		return (cmd);
	if (!s)
		return (NULL);
	sp = ft_split(s, ':');
	i = -1;
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
