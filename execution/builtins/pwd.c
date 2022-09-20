#include "../../includes/execution.h"

void	ex_pwd(char **sp, t_envp *my_env, int out)
{
	if (sp[1])
		printf("pwd: too many arguments\n");
	else {
        if (my_env->PWD == NULL)
            my_env->PWD = getcwd(NULL, sizeof(my_env->PWD));
        ft_putstr_fd(my_env->PWD, out);
        write(out, "\n", 1);
    }
	my_env->status = 0;
}
