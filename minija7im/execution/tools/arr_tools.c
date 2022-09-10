#include "../../includes/execution.h"


size_t	arr_size(char *env[])
{
	size_t i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	fill_arr(char *env[], char *s[])
{
	int i;

	i = 0;
	while (env[i])
	{
		s[i] = ft_strdup(env[i]);
		i++;
	}
	s[i] = 0;
}
