/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/03 13:18:09 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_minishell	minishile;

	char *buf;
	while(1)
	{
		buf = readline("\033[0;33m minishell >\033[0m");
		// printf("buf : %s\nwayiih", buf);
		if (ft_strncmp(buf, "exit", 4) == 0)
			return(0);
		pipex(ac, buf, env);
		free(buf);
	}
	return (0);
}
