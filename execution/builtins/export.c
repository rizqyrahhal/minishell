#include "../../includes/execution.h"

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

void	ex_export(char **sp, t_envp *my_env, int out)
{
	// char **s;
	int		i;
	char*	s;
	// int		status;
	// oldpwd at first
	i = 1;
	if (sp[1] == NULL)
		export_(my_env->env, out);
	while (sp[i]) {
		if (sp[1][0] == '-') {
			s = ft_strjoin("minishell: export: ", sp[1]);
			s = ft_strjoin(s, ": invalid option\n");
			ft_putstr_fd(s, 2);
			ft_putstr_fd("export: usage: export [-nf] [name[=value] ...] or export -p\n", 2);
			return ;
		}
		my_env->status = ft_add2env(my_env, sp[i]);
		i++;
	}
}
