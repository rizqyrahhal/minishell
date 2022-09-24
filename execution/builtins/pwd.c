#include "../../includes/execution.h"

void	ex_pwd(char **sp, t_envp *my_env, int out)
{
	char*	pwd;
	if (sp[1])
		printf("pwd: too many arguments\n");
	else {
		pwd = getcwd(NULL, sizeof(my_env->PWD));
		if (!pwd)
			pwd = my_env->PWD;
		ft_putstr_fd(pwd, out);
		write(out, "\n", 1);
    }
	my_env->status = 0;
}
