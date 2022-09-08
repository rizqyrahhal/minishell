#include "../Includes/minishell.h"
#include "readline/history.h"
#include <string.h>
#include <ctype.h>

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
	}
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

void	print_q(char *s)
{
	int i;

	i = -1;
	printf("declare -x ");
	while (s[++i] && s[i] != '=')
		printf("%c", s[i]);
	printf("%c", s[i]);
	if (sea_rch(s, '=')) {
		printf("\"");
		while (s[++i])
			printf("%c", s[i]);
		printf("\"\n");
	}
	else
		printf("\n");

}

void	export_(char **arr)
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
		print_q(s[c]);
		s = ft_removee(s, s[c]);
		i++;
	}
}