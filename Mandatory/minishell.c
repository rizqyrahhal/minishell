/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/05 17:44:27 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_command	*command;
	t_minishell *minishell;


	char *buf;
	command = malloc(sizeof(t_command) * 2);
	command[0].arry = malloc(sizeof(char*) * 3);
	command[1].arry = malloc(sizeof(char*) * 3);
	command[0].arry[0] = "ls";
	command[0].arry[1] = "-la";
	command[0].arry[2] = 0;
	command[1].arry[0] = "cat";
	command[1].arry[1] = "-e";
	command[1].arry[2] = 0;
	// printf("%s\n %s\n %s\n %s\n",command[0].arry[0], command[0].arry[1], command[1].arry[0], command[1].arry[1]);
	while(1)
	{
		buf = readline("\033[0;33m minishell >\033[0m");
		// printf("buf : %s\n", buf);
		if (ft_strncmp(buf, "exit\0", 5) == 0)
			return(0);
		pipex(ac, buf, env);
		free(buf);
	}
	return (0);
}
