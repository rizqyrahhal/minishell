#include "../../includes/execution.h"


void	ex_env(char **sp, t_envp *my_env)
{
	int		i;
	int 	status;

	i = 1;
	if (sp[1] == NULL)
		print_ar(my_env->env);
	else
		fprintf(stderr, "options or arguments not required\n");
	my_env->status = 0;
}

