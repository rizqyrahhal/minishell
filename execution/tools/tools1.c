#include "../../includes/execution.h"

int	sea_rch(char *s, int a)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

void	arr_deletee(char **my_env, char **s, char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (my_env[j])
	{
		if (ft_strncmp(my_env[j], str, ft_strlen(str)) == 0 && ft_strlen(str) == ft_strlen(my_env[j])) {
			j++;
		}
		else
			s[i++] = ft_strdup(my_env[j++]);
		free(my_env[j - 1]);
	}
	free(my_env);
	s[i] = NULL;
}

int __sort(char **s)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (ft_strcmp(s[k], s[i]) == 1)
			k = i;
		i++;
	}
	return (k);
}

char**	ft_removee(char *my_env[], char *var)
{
	int k;
	char **s;


	k = arr_size(my_env);
	s = malloc(k * sizeof (char*));
	arr_deletee(my_env, s, var);
	return (s);
}

void	print_q(char *s, int out)
{
	int i;

	i = -1;
	ft_putstr_fd("declare -x ", out);
	while (s[++i] && s[i] != '=')
		write(out, &s[i], 1);
    write(out, &s[i], 1);
	if (sea_rch(s, '=')) {
		write(out, "\"", 1);
		while (s[++i])
			write(out, &s[i], 1);
		write(out, "\"\n", 2);
	}
	else
		write(out, "\n", 1);

}

void	export_(char **arr, int out)
{
	int i;
	int c;
	char **s;

	i = 0;
	c = 0;
	s = malloc((arr_size(arr) + 1) * sizeof (char*));
	fill_arr(arr, s);
	while (arr_size(s) > 0)
	{
		c = __sort(s);
		print_q(s[c], out);
		s = ft_removee(s, s[c]);
		i++;
	}
}