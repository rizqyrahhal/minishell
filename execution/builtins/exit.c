#include "../../includes/execution.h"

void	ex_exit(char **sp, t_envp *myenv)
{
	long	num;

	if (sp[1] && !is_str(sp[1])) {
		printf("exit\nminishell: exit: %s: numeric argument required\n", sp[1]);
		myenv->status = 255;
		exit (255);
	}
	if (sp[1] && sp[2] != NULL) {
		printf("exit\nminishell: exit: too many arguments\n");
		myenv->status = 1;
	}
	else
	{
	printf("exit\n");
		num = ft_atoi(sp[1]);
		if (sp[1])
			myenv->status = num % 256;
		exit(myenv->status);
	}
}