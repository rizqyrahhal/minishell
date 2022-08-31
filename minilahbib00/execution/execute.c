/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:42:12 by lsemlali          #+#    #+#             */
/*   Updated: 2022/07/02 19:57:54 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

char*	_home(char *env[])
{
	int	i;
	int j;

	i = 0;

	while (env[i])
	{
		if (ft_strncmp("HOME", ft_substr(env[i], 0, 4), 4) == 0)
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		i++;
	}
	return (NULL);
}

int check_var(char *var, int a)
{
	int i;
	int	k;

	k = 0;
	while (var[k] && var[k] != '=')
		k++;
	if (var[k - 1] == '+' && a == 1)
		k--;
	i = 0;
	while (i < k)
	{
		if (!ft_isvalid(var[i])) {
			return (0);
		}
		i++;
	}
	return (1);
}

char**	ft_add2env(char *my_env[], char *var)
{
	int k;
	int i;
	char **s;

	if (!check_var(var, 1)) {
		fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", var);
		return (my_env);
	}
	k = arr_size(my_env);
	i = 0;
	while (my_env[i]) {
		if (arr_s(my_env[i], var)) {
			k--;
			break ;
		}
		i++;
	}
	s = malloc((k + 2) * sizeof (char*));
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i - 1] == '+')
		arr_app(my_env, s, var);
	else
		arr_cpy(my_env, s, var);
	return (s);
}

char**	ft_remove(char *my_env[], char *var)
{
	int k;
	char **s;

	if (!check_var(var, 0)) {
		fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n", var);
		return (my_env);
	}

	k = arr_size(my_env);
	s = malloc(k * sizeof (char*));
	arr_delete(my_env, s, var);
	return (s);
}

void __builtins(char **sp, t_envp *my_env)
{
	char **vars;
	char cwd[256];
	char old_cwd[256];
	int i;
	int k;

	i = 1;
	k = 5;
	if (ft_strncmp(sp[0], "cd", 2) == 0 && ft_strlen(sp[0]) == 2) {
		if (sp[1] == NULL) {
			chdir(_home(my_env->env));
		} else {
			getcwd(old_cwd, sizeof(old_cwd));
			chdir(sp[1]);
			getcwd(cwd, sizeof(cwd));
			printf("--%s--\n", cwd);
			my_env->env = ft_add2env(my_env->env, ft_strjoin("PWD=", cwd));
			my_env->env = ft_add2env(my_env->env, ft_strjoin("OLDPWD=", old_cwd));
		}
	}
	if (ft_strncmp(sp[0], "export", 6) == 0 && ft_strlen(sp[0]) == 6) {
//		fprintf(stderr, "%s---+----%s\n", my_env->env[5], sp[1]);
		if (sp[1] == NULL)
			export_(my_env->env);
		while (sp[i]) {
			my_env->env = ft_add2env(my_env->env, sp[i]);
			i++;
		}
//		fprintf(stderr, "%s---\n", my_env->env[5]);
	}
	if (ft_strncmp(sp[0], "env", 3) == 0 && ft_strlen(sp[0]) == 3) {
		if (sp[1] == NULL)
			print_ar(my_env->env);
		while (sp[i]) {
			my_env->env = ft_add2env(my_env->env, sp[i]);
			i++;
		}
	}
	if (ft_strncmp(sp[0], "unset", 5) == 0 && ft_strlen(sp[0]) == 5) {
		while (sp[i]) {
			my_env->env = ft_remove(my_env->env, sp[i]);
			i++;
		}
//		print_ar(my_env->env);
	}
	if (ft_strncmp(sp[0], "pwd", 3) == 0 && ft_strlen(sp[0]) == 3) {
		getcwd(cwd, sizeof (cwd));
		printf("%s\n", cwd);
	}
	if (ft_strncmp(sp[0], "exit", 4) == 0 && ft_strlen(sp[0]) == 4)
		exit(1);
}

void	ex_comm(t_pipe p, int k, t_command **cmd, char *env[])
{
	int	i;
	int	a;
//	if (k == 4)
//		ac--;
	i = -1;
	a = 1;
	while (++i < k - 1)
	{
//		fprintf(stderr, "********%s\n", (*cmd)->cmd[0]);
		next_cmd(env, &p, i, *cmd);
		close(p.fd[i][0]);
		close(p.fd[i][1]);
		*cmd = (*cmd)->next;
	}
}

void	f_close(t_pipe p, int k)
{
	int	i;

	i = -1;
	while (++i < k)
	{
		close(p.fd[i][0]);
		close(p.fd[i][1]);
	}
}


void	multiple_p(t_pipe p, int k, t_command *cmd, t_envp *my_env)
{
	p.pid1 = fork();
	if (p.pid1 == 0) {
		if (cmd->infile != -1)
			frst_cmd(my_env->env, p.fd[0], cmd);
	}
	else {
		ex_comm(p, k, &cmd->next, my_env->env);
//		fprintf(stderr, "+++%s\n", cmd->cmd[0]);
		//fprintf(stderr, "%s\n", cmd->next->next->cmd[0]);
		p.pid2 = fork();
		if (p.pid2 == 0)
			last_cmd(my_env->env, p.fd[k - 1], cmd->next);
		f_close(p, k);
		while (wait(NULL) != -1);
	}
}

int is_built(char *s)
{
	if (ft_strncmp(s, "cd", 2) == 0 && ft_strlen(s) == 2)
		return (1);
	if (ft_strncmp(s, "export", 6) == 0 && ft_strlen(s) == 6)
		return (1);
	if (ft_strncmp(s, "unset", 5) == 0 && ft_strlen(s) == 5)
		return (1);
	if (ft_strncmp(s, "env", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	if (ft_strncmp(s, "pwd", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	if (ft_strncmp(s, "exit", 4) == 0 && ft_strlen(s) == 4)
		return (1);
	return (0);
}

void	child(t_pipe p, int k, t_command *cmd, t_envp *my_env)
{
//	if (p.cm == 3)
//		k = ac - 6;
	if (k > 0)
		multiple_p(p, k, cmd, my_env);
	else
	{
		p.pid1 = fork();
		if (p.pid1 == 0) {
			if (!is_built(cmd->cmd[0]))
				one_cmd(my_env->env, cmd);
			else
				exit (0);
		}
		else {
			__builtins(cmd->cmd, my_env);
			while (wait(NULL) != -1);
		}
	}
}

int	pipes(int k, t_command *cmd, t_envp *my_env)
{
	t_pipe	p;
	int		i;

	i = -1;
	p.fd = malloc(k * sizeof(int *));
	while (++i < k)
	{
		p.fd[i] = malloc(2 * sizeof(int));
		pipe(p.fd[i]);
	}
//	if (ft_strncmp(av[1], "here_doc\0", 9) == 0)
//		p.file1 = here_doc(av[2], &p, av[ac - 1]);
//	else
//	{
//	p.cm = 2;
//	}
//	if (p.file1 == -1)
//		put_error(ft_strjoin(av[1], " : No such file or directory\n"), 1);
	child(p, k, cmd, my_env);
	return (0);
}
