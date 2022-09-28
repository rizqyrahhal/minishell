/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:54 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/28 15:54:10 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	get_current(char **sp, t_envp *my_env, int k, char *old_cwd)
{
	char	cwd[256];

	if (chdir(sp[1]) == 0 && k == 0)
	{
		if (!getcwd(cwd, sizeof(cwd)))
		{
			ft_add2env(my_env, "PWD+=/..");
			my_env->pwd = ft_strjoin(my_env->pwd, "/..");
			printf("cd: error retrieving current directory: getcwd: cannot ");
			printf("access parent directories: No such file or directory\n");
			my_env->status = 0;
		}
		else
		{
			ft_add2env(my_env, ft_strjoin("PWD=", cwd));
			my_env->pwd = ft_strdup(cwd);
			ft_add2env(my_env, ft_strjoin("OLDPWD=", old_cwd));
		}
	}
	else if (k == 0)
	{
		perror(ft_strjoin("minishell: cd: ", sp[1]));
		my_env->status = 1;
	}
}

void	get_old(char **sp, t_envp *my_env)
{
	char	old_cwd[256];
	int		k;

	k = 0;
	if (!getcwd(old_cwd, sizeof(old_cwd)))
	{
		if (sp[1] && sp[1][0] == '.' && ft_strlen(sp[1]) == 1)
		{
			ft_add2env(my_env, "PWD+=/.");
			ft_add2env(my_env, ft_strjoin("OLDPWD=", my_env->pwd));
			my_env->pwd = ft_strjoin(my_env->pwd, "/.");
			printf("cd: error retrieving current directory: getcwd: cannot ");
			printf("access parent directories: No such file or directory\n");
			my_env->status = 0;
			k++;
		}
	}
	get_current(sp, my_env, k, old_cwd);
}

void	ex_cd(char **sp, t_envp *my_env)
{
	if (sp[1] == NULL || (sp[1][0] == '~' && ft_strlen(sp[1]) == 1))
	{
		if (arr_s(my_env->env, "HOME") == -1 && !sp[1])
		{
			printf("minishell: cd: HOME not set\n");
			my_env->status = 1;
		}
		else
			chdir(getenv("HOME"));
	}
	else
		get_old(sp, my_env);
}
