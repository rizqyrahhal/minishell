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

int arr_s(char *s, char *str)
{
	int i;
	int k;

	i = 0;
	k = ft_strlen(str);
	while (s[i] && s[i] != '=')
		i++;
	if (str[k - 1] == '+')
		k--;
	if (ft_strncmp(s, str, k) == 0 && k == i)
		return (1);
	return (0);
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

	sp = ft_split(str, '=');
	while (my_env[i]) {
		if (arr_s(my_env[i], sp[0])) {
			k = i;
			break ;
		}
		i++;
	}
	i = 0;
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
	k = -1;

	sp = ft_split(str, '=');
	while (my_env[i]) {
		if (arr_s(my_env[i], sp[0])) {
			k = i;
			break ;
		}
		i++;
	}
	i = 0;
			printf("waaaaaaaaayli%d\n", k);
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

	i = 0;
	j = 0;
	while (my_env[j])
	{
		if (arr_s(my_env[j], str)) {
			j++;
		}
		else
			s[i++] = ft_strdup(my_env[j++]);
	}
	s[i] = NULL;
}