/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/22 02:14:34 by rarahhal         ###   ########.fr       */
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

// typedef struct s_rediriction_node
// {
// 	int	type;
// 	char*	file;
// 	struct s_rediriction_node *next;
// } t_redirection;

// typedef struct s_redirection
// {
// 	int		input; // < if input != 0
// 	int		output; // > if output != 1
// 	// int		type;
// 	// char*		file_name;
// }	t_redirection;

typedef struct s_command_node
{
	char*	cmd;
	int		input; // < if input != 0
	int		output; // > if output != 1
	struct s_command_node *next;
} t_command;

typedef struct s_envp
{
	char	**env; // hna fin ghanzido ila exporta chi variable bar realooc wola ghanm7iwh 
	// char	*path; ///// bach nstoki hna path !!!!!!!!WALAKIN KHASNA NRODO LBAL LA UNSITE LINA LPATH WO NB9AW KHADAMIN BHADA!!!!!!!
	// char	*variabls; ///// nstoki hna variablse li exportaw est apre nzido fi envp
}	t_envp;

typedef struct s_minishell
{
	char			*buf;
	size_t			buf_sizeline;
	t_command		*command; // reallooc pour chaque cmd trete
	int 			nbr_command;
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