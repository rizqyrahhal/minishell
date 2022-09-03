#include "../Includes/minishell.h"

int check_var(char *var, int a)
{
	int i;
	int	k;

	k = 0;
	while (var[k] && var[k] != '=')
		k++;
	if (var[k - 1] == '+' && a == 1)
		k--;
	i = 0;
	if (var[i] == '"')
	{
		while (var[i] && var[i] == '"')
			i++;
	}
	while (i < k)
	{
		if (!ft_isvalid(var[i])) {
			return (0);
		}
		i++;
	}
	return (1);
}

char *new_var(char *var)
{
	char	*new_var;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_var = malloc(ft_strlen(var));
	new_var[ft_strlen(var) - 1] = 0;
	while (var[i])
	{
		if (var[i] == '+')
			i++;
		new_var[j] = var[i];
		j++;
		i++;
	}
	return (new_var);
}

char**	ft_add2env(char *my_env[], char *var)
{
	int k;
	int i;
	char **s;


	if (!check_var(var, 1) || ft_isdigit(var[0])) {
		fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", var);
		r = 1;
		exit (1);
	}
	k = arr_size(my_env);
	i = 0;
	while (my_env[i]) {
		if (arr_s(my_env[i], var)) {
			k--;
			break ;
		}
		i++;
	}
	s = malloc((k + 2) * sizeof (char*));
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i - 1] == '+')
		arr_app(my_env, s, new_var(var));
	else
		arr_cpy(my_env, s, var);
	r = 0;
	return (s);
}

char**	ft_remove(char *my_env[], char *var)
{
	int k;
	char **s;

	if (!check_var(var, 0)) {
		fprintf(stderr, "minishell: unset: `%s': not a valid identifier\n", var);
		r = 1;
		exit (1);
	}

	k = arr_size(my_env);
	s = malloc(k * sizeof (char*));
	arr_delete(my_env, s, var);
	r = 0;
	return (s);
}
