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
//# include "../pipe/pipex.h"
# include "../pipes/pipex.h"

typedef struct s_exp
{
	char	*var;
    char    *value;// alloca nmbr of command
}   t_exp;

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


t_command*	ft_lstlast(t_command* list);
void	ft_addfront(t_command**	list, t_command *new);
t_command*	ft_lstnew(char** cmd_data, int infile, int outfile);
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