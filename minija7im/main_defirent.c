/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_defirent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 10:19:57 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/09 16:05:34 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char	*delimiteurs = "<>|<<$>>";
char	*respP[20];
char	*respout[10];
char	*respin[10];
char	*tube[10];
char	mot[50];
int		symboleP, status, c;


int	main(int ac, char *av[], char *env[])
{
	t_command	*command;
	t_minishell minishell;

	while(1)
	{
		minishell.buf = readline("\033[0;33m minishell >\033[0m");
		// printf("buf : %s\n", minishell.buf);
		minishell.buf_sizeline = strlen(minishell.buf);
		//prsing(&minishell);
		if (strncmp(minishell.buf, "exit\0", 5) == 0)
			return(0);
		free(minishell.buf);
	}
	return (0);
}