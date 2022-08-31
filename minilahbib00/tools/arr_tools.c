#include "../Includes/minishell.h"
#include "readline/history.h"
#include <string.h>
#include <ctype.h>

int arr_size(char *env[])
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char    *ft_cpy(char *s, int k)
{
	char    *var;
	int     i;
	i = 0;
	var = malloc(k + 1);
	var[k] = 0;
	while (i < k)
	{
		var[i] = s[i];
		i++;
	}
	return (var);
}

void	fill_arr(char *env[], char *s[])
{
	int i;

	i = 0;
	while (env[i])
	{
		s[i] = ft_cpy(env[i], ft_strlen(env[i]));
		i++;
	}
	s[i] = 0;
}
