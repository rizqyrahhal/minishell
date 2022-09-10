#include "../../includes/execution.h"

int check_unset(char *var)
{
	int i;

	i = 0;
	if (ft_isdigit(var[0]))
		return (0);
	while (var[i])
	{
		if (!ft_isvalid(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ex_unset(char **sp, t_envp *my_env)
{
	int		i;
	int 	status;

	i = 1;
	if (sp[1] && sp[1][0] == '-')
		printf("options not required\n");
	else {
		while (sp[i]) {
			my_env->status = ft_remove(my_env, sp[i]);
			i++;
		}
	}
	r = 0;
}