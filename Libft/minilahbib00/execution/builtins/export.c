#include "../../Includes/minishell.h"

int check_export(char *var)
{
	int i;
	int	k;

	k = 0;
	while (var[k] && var[k] != '=')
		k++;
	if (var[k - 1] == '+' && var[k] == '\0')
		return (0);
	if (var[k - 1] == '+')
		k--;
	i = 0;
	if (ft_isdigit(var[0]) || !ft_isvalid(var[0]))
		return (0);
	while (i < k)
	{
		if (!ft_isvalid(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ex_export(char **sp, t_envp *my_env)
{
	char **s;
	int		i;
	int		status;
	// oldpwd at first
	i = 1;

	if (sp[1] == NULL)
		export_(my_env->env);
	while (sp[i]) {
		my_env->status = ft_add2env(my_env, sp[i]);
		i++;
	}
	printf("hello\n");
}
