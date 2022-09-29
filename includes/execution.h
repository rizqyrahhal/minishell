/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:43:36 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/29 21:52:37 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H


# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "../execut_libft/ex_libft.h"
# include "minishell.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_exp
{
	char	*var;
	char    *value;
	struct s_exp *next;
}   t_exp;

typedef struct s_pipe
{
	int	file1;
	int	file2;
	pid_t 	pid1;
	pid_t 	pid2;
	int	**fd;
	pid_t 	id[1024];
	int	check;
	int	cm;
}	t_pipe;


// builtins
void	ex_cd(char **sp, t_envp *my_env);
void	ex_env(char **sp, t_envp *my_env, int out);
void	ex_export(char **sp, t_envp *my_env, int out);
void	ex_unset(char **sp, t_envp *my_env);
void	ex_pwd(char **sp, t_envp *my_env, int out);
void	ex_echo(char **sp, t_envp *my_env, int out);
void	ex_exit(char **sp, t_envp *my_env);
int		is_built(char *s);
void	__builtins(char **sp, t_envp *my_env, int out);

//builtins_tools
int		ft_remove(t_envp *myenv, char *var);
int		ft_add2env(t_envp *myenv, char *var);
int 	check_var(char *var, int a);
int		check_unset(char *var);
int		check_export(char *var);



//expand

int		is_str(char *s);
int		ft_isvalid(int c);
//void	arr_app(t_envp *my_env, char **s, char *str);
void	export_(char **arr, int out);
void	print_ar(char **arr, int out);
int 	arr_s(char **s, char *str);
void	arr_cpy(t_envp *my_env, char *str);
void	arr_delete(t_envp *my_env, char **s, char *str);
char    *ft_cpy(char *s, int k);
size_t	arr_size(char *env[]);
void	fill_arr(char *env[], char *s[]);


// Execute
int		pipes(int ac, t_command *cmd, t_envp *my_env);
void	multiple_p(t_pipe *p, int k, t_command *cmd, t_envp *my_env);
void	main_p(t_pipe *p, int k, t_command *cmd, t_envp *my_env);
void	main_wait(t_pipe *p, int k, t_envp *my_env, int ch);
t_command	*ex_comm(t_pipe *p, int k, t_command *cmd, t_envp *my_env);
void	__builtins(char **sp, t_envp *my_env, int out);
int		is_built(char *s);
void	f_close(t_pipe *p, int k);



char	*get_path(char *s, char *cmd);
void	one_cmd(t_envp *my_env, t_command *cmd);
void	frst_cmd(t_envp *my_env, int *fd, t_command *cmd);
void	next_cmd(t_envp *my_env, t_pipe *p, int i, t_command *cmd);
void	last_cmd(t_envp *my_env, int *fd, t_command *cmd);
void	ex_ecu(char *path, char *sp[], t_envp *my_env, int out);
void	ft_norm__(t_envp *my_env, t_pipe *p, int i, t_command *cmd);
void	er_ror(char *err, char *s);
int		sea_rch(char *s, int a);
char	*handle_env(char *env[]);
char	*skip_sl(char	*cmd);
char	*get_path(char *s, char *cmd);
void	ft_exit(char *sp[]);
void	free_arr(char **s);

#endif