/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/06 19:10:21 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include "../pipe/pipex.h"

typedef struct s_command
{
	char	**arry; // alloca nmbr of command
}   t_command;

typedef struct s_redirection
{
	int		input; // < if input != 0
	int		output; // > if output != 1
}	t_redirection;

typedef struct s_envp
{
	char	**env;
	char	*path;
	char	*variabls;
}	t_envp;

typedef struct s_minishell
{
	t_command		*command; // reallooc pour chaque cmd trete
	int 			nbr_command;
	t_redirection	redirection;
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