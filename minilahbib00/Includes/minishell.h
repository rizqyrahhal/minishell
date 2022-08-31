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
# include "../Libft/libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_command
{
	char**	cmd;
	int		infile; // < if input != 0
	int		outfile; // > if output != 1
	struct s_command *next;
} t_command;

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
	char 	**export;
	char	*path;
	char	*variabls;
}	t_envp;

typedef struct s_minishell
{
	t_command		*command; // reallooc pour chaque cmd trete
	int 			nbr_command;
	t_redirection	redirection;
}   t_minishell;




typedef struct s_pipe
{
	int	file1;
	int	file2;
	int	pid1;
	int	pid2;
	int	**fd;
	int	id[99];
	int	check;
	int	cm;
}	t_pipe;


int		ft_isvalid(int c);
void	arr_app(char **my_env, char **s, char *str);
void	export_(char **arr);
void	print_ar(char **arr);
int 	arr_s(char *s, char *str);
void	arr_cpy(char **my_env, char **s, char *str);
void	arr_delete(char **my_env, char **s, char *str);
char    *ft_cpy(char *s, int k);
int		arr_size(char *env[]);
void	fill_arr(char *env[], char *s[]);
int		pipes(int ac, t_command *cmd, t_envp	*my_env);
char	*get_path(char *s, char *cmd);
void	one_cmd(char **env, t_command *cmd);
void	frst_cmd(char **env, int *fd, t_command *cmd);
void	next_cmd(char **env, t_pipe *p, int i, t_command *cmd);
void	last_cmd(char **env, int *fd, t_command *cmd);
void	put_error(char *s, int h);
int		sea_rch(char *s, int a);
char	*handle_env(char *env[]);
char	*skip_sl(char	*cmd);
char	*get_path(char *s, char *cmd);
void	ft_exit(char *sp[]);
int		here_doc(char *str, t_pipe *p, char *file);
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