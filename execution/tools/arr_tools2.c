#include "../../includes/execution.h"


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

void	arr_cpy(t_envp *my_env, char *str)
{
	char	**s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = malloc((arr_size(my_env->env) + 1) * sizeof (char*));
	while (my_env->env[j])
	{
		if (i == 5)
			s[i] = ft_strdup(str);
		else
			s[i] = ft_strdup(my_env->env[j++]);
		i++;
	}
	s[i] = NULL;
	free(my_env->env);
	my_env->env = s;
}

//void	arr_app(t_envp *my_env, char *str)
//{
//	char	**s;
//	int		i;
//	int		j;
//	int 	k;
//
//	i = 0;
//	j = 0;
//
//	sp = spl(str);
//	i = 0;
//	while (my_env->env[j])
//	{
//		if (k != -1 && j == k) {
//			s[i] = ft_strjoin(my_env->env[j], sp[1]);
//			j++;
//		}
//		else if (i == 5 && k == -1)
//			s[i] = ft_strdup(str);
//		else
//			s[i] = ft_strdup(my_env->env[j++]);
//		i++;
//	}
//	s[i] = NULL;
//}

void	arr_delete(t_envp *my_env, char **s, char *str)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = arr_s(my_env->env, str);
	while (my_env->env[j])
	{
		if (j == k)
			j++;
		else
			s[i++] = ft_strdup(my_env->env[j++]);
	}
	s[i] = NULL;
}