#include "../Includes/minishell.h"
#include "readline/history.h"
#include <string.h>
#include <ctype.h>

void	print_ar(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (sea_rch(arr[i], '='))
			printf("%s\n", arr[i]);
		i++;
	}
}

int arr_s(char **s, char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (str[k] && str[k] != '=')
		k++;
	if (str[k - 1] == '+')
		k--;
	while (s[i]) {
		j = 0;
		while (s[i][j] && s[i][j] != '=')
			j++;
		if (ft_strncmp(s[i], str, k) == 0 && k == j)
			return (i);
		i++;
	}
	return (-1);
}

char **spl(char *s)
{
	int		i;
	char**	sp;

	sp = malloc(3 * sizeof (char*));
	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	sp[0] = ft_substr(s, 0, i);
	if (s[i] && s[i + 1])
		sp[1] = ft_substr(s, i + 1, ft_strlen(s) - i - 1);
	else
		sp[1] = NULL;
	sp[2] = NULL;
	return (sp);
}

void	arr_cpy(char **my_env, char **s, char *str)
{
	char	**sp;
	int		i;
	int		j;
	int 	k;

	i = 0;
	j = 0;
	k = -1;

	sp = spl(str);
	k = arr_s(my_env, sp[0]);
	while (my_env[j])
	{
		if (k != -1 && j == k) {
			s[i] = ft_strdup(str);
			j++;
		}
		else if (i == 5 && k == -1)
			s[i] = ft_strdup(str);
		else
			s[i] = ft_strdup(my_env[j++]);
		i++;
	}
	s[i] = NULL;
}

void	arr_app(char **my_env, char **s, char *str)
{
	char	**sp;
	int		i;
	int		j;
	int 	k;

	i = 0;
	j = 0;
	sp = spl(str);
	k = arr_s(my_env, sp[0]);
	i = 0;
	while (my_env[j])
	{
		if (k != -1 && j == k) {
			s[i] = ft_strjoin(my_env[j], sp[1]);
			j++;
		}
		else if (i == 5 && k == -1)
			s[i] = ft_strdup(str);
		else
			s[i] = ft_strdup(my_env[j++]);
		i++;
	}
	s[i] = NULL;
}

void	arr_delete(char **my_env, char **s, char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = arr_s(my_env, str);
	while (my_env[j])
	{
		if (j == k)
			j++;
		else
			s[i++] = ft_strdup(my_env[j++]);
	}
	s[i] = NULL;
}