/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/08 11:01:13 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../mini_pipex/includs/pipex.h"

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
	char			*buf;
	size_t			buf_sizeline;
	t_command		*command; // reallooc pour chaque cmd trete
	int 			nbr_command;
	t_redirection	redirection;
}   t_minishell;

// parsing
void	prsing(t_minishell *minishell);


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