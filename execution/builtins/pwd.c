#include "../../includes/execution.h"

void	ex_pwd(char **sp, t_envp *my_env)
{
	if (sp[1])
		printf("pwd: too many arguments\n");
	else
		printf("%s\n", my_env->PWD);
	my_env->status = 0;
}
