#include "../../includes/execution.h"

void	ex_exit(char **sp, t_envp *myenv)
{
	if (sp[1] && sp[2] != NULL) {
		printf("exit\nminishell: exit: too many arguments\n");
		myenv->status = 1;
		exit (1);
	}
	else if (sp[1] && !is_str(sp[1])) {
		printf("exit\nminishell: exit: %s: numeric argument required\n", sp[1]);
		myenv->status = 255;
		exit (255);
	}
	printf("exit\n");
	if (sp[1])
		myenv->status = ft_atoi(sp[1]) % 256;
	exit(myenv->status);
}