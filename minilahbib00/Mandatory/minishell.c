/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/11 18:56:23 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int	sea_rrch(char *s, int a)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	ft_countt(char *s, int a)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == a)
			count++;
		i++;
	}
	return (count);
}

int	main(int ac, char *av[], char *env[])
{
	t_command	*command;
	char **s;
	char *buf;
	int k = 0;

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
		buf = readline("\033[0;33m minishell > \033[0m");
		k = ft_countt(buf, '|');
		if ()
		if (k >= 1)
		{
			s = ft_split(buf, '|');
			if (ft_strncmp(s))
			if (k > 1)
				mpipex(k, s, env);
			else
				dpipex(ac, s, env);
			free(s);
		}
		else
			pipex(ac, buf, env);
		free(buf);
	}
	return (0);
}
