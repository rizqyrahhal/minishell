/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/03 11:14:21 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include "../pipex/includs/pipex.h"

typedef struct s_command
{
	int 	nbr_command;
	char	**arry; // alloca nmbr of command
	
}   t_command;


typedef struct s_envp
{
	char	**env;
	char	*path;
	char	*variabls;
}	t_envp;



typedef struct s_minishell
{
	t_command	command;
}   t_minishell;

/*
pipe
< >

comd
int indx nmbre_cmd
**ary [0].cmd ....argm

rediriction
< >

signals
*/

#endif