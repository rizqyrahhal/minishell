#include "../../Includes/minishell.h"

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

int check_oldv(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (s[i] != '=')
		return 1;
	else{
		if (s[i + 1] == '\0')
			return (1);
	}
	return (0);
}

char**	ft_add2env(char *my_env[], char *var)
{
	int k;
	int i;
	char **s;


	if (!check_export(var)) {
		fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", var);
		r = 1;
		return (my_env);
	}
	k = arr_size(my_env);
	i = 0;
	if (arr_s(my_env, var) != -1)
		k--;
	s = malloc((k + 2) * sizeof (char*));
	i = 0;
	k = arr_s(my_env, var);
	if (k != -1 && check_oldv(my_env[k])) {
		my_env[k] = ft_strdup(new_var(var));
		return (my_env);
	}
	while (var[i] && var[i] != '=')
		i++;
	if (var[i - 1] == '+') {
		if (k != -1 && (var[i] != '=' || var[i + 1] == '\0'))
			return (my_env);
		arr_app(my_env, s, new_var(var));
	}
	else {
		if (k != -1 && (var[i] != '=' || var[i + 1] == '\0'))
			return (my_env);
		arr_cpy(my_env, s, var);
	}
	r = 0;
	return (s);
}

char**	ft_remove(char *my_env[], char *var)
{
	int k;
	char **s;

	if (!check_unset(var)) {
		printf("minishell: unset: `%s': not a valid identifier\n", var);
		r = 1;
		return (my_env);
	}
	if (arr_s(my_env, var))
		return (my_env);
	k = arr_size(my_env);
	s = malloc(k * sizeof (char*));
	arr_delete(my_env, s, var);
	r = 0;
	return (s);
}
