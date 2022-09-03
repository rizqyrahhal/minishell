#include "../Includes/minishell.h"

void	ex_cd(char **sp, t_envp *my_env)
{
	char	cwd[256];
	char	old_cwd[256];

	if (sp[1] == NULL)
		chdir(getenv("HOME"));
	else {
		getcwd(old_cwd, sizeof(old_cwd));
		chdir(sp[1]);
		getcwd(cwd, sizeof(cwd));
		printf("--%s--\n", cwd);
		my_env->env = ft_add2env(my_env->env, ft_strjoin("PWD=", cwd));
		my_env->env = ft_add2env(my_env->env, ft_strjoin("OLDPWD=", old_cwd));
	}
	r = 0;
}

void	ex_export(char **sp, t_envp *my_env)
{
	char **s;
	int		i;
	int		status;

	i = 1;

	if (sp[1] == NULL)
		export_(my_env->env);
	while (sp[i]) {
		my_env->env = ft_add2env(my_env->env, sp[i]);
		i++;
	}
}

void	ex_env(char **sp, t_envp *my_env)
{
	int		i;
	int 	status;

	i = 1;
	if (sp[1] == NULL)
		print_ar(my_env->env);
	while (sp[i]) {
		my_env->env = ft_add2env(my_env->env, sp[i]);
		i++;
	}
	r = 0;
}

void	ex_pwd(char **sp, t_envp *my_env)
{
	char cwd[256];
	getcwd(cwd, sizeof (cwd));
	printf("%s\n", cwd);
}

void	ex_unset(char **sp, t_envp *my_env)
{
	int		i;
	int 	status;

	i = 1;
	while (sp[i]) {
		my_env->env = ft_remove(my_env->env, sp[i]);
		i++;
	}
	r = 0;
}

void	ex_exit(char **sp)
{
	if (sp[2] != NULL) {
		fprintf(stderr, "exit\nminishell: exit: too many arguments\n");
		r = 1;
		fprintf(stderr, "%d\n", r);
		exit (1);
	}
	if (!is_str(sp[1])) {
		fprintf(stderr, "exit\nminishell: exit: %s: numeric argument required\n", sp[1]);
		r = 255;
		fprintf(stderr, "%d\n", r);
		exit (255);
	}
	fprintf(stderr, "exit\n");
	r = ft_atoi(sp[1]) % 256;
	fprintf(stderr, "%d\n", r);
	exit(0);
}