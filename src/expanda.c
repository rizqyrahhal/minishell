#include "../includes/execution.h"

t_exp	*lst_last(t_exp* list)
{
	while (list)
	{
		if (!list->next) {
			return (list);
		}
		list = list->next;
	}
	return (list);
}

void	add_front(t_exp **list, t_exp *new)
{
	t_exp	*tmp;

	new->next = NULL;
	if (*list == NULL)
		*list = new;
	else
	{
		if (*list)
		{
			tmp = lst_last(*list);
			tmp->next = new;
		}
		else
			*list = new;
	}
}

t_exp *ft_getVar(char *env[], t_exp *exp)
{
	int 	i;
	int 	j;
	char	*str;
	t_exp	*tmp;

	j = 0;
	i = 0;
	while (env[i])
	{
		tmp = malloc(sizeof (t_exp));
		while (env[i][j] != '=')
			j++;
		str = ft_cpy(env[i], j++);
		tmp->var = ft_strjoin("$", str);
		tmp->value = ft_cpy(&env[i][j], ft_strlen(&env[i][j]));
		add_front(&exp, tmp);
		j = 0;
		i++;
		tmp = NULL;
		free(str);
	}
	return (exp);
}

int	ft_isvalid(int c)
{
	if ((c <= 'z' && c >= 'a') || (c >= 'A' && c <= 'Z') || c == '_'
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	return (0);
}

char* ft_replace(char* s, char* old, char* new, int *k)
{
	char*	result;
	int 	i;
	int 	j;
	int		idx;

	i = *k - 1;
	while (s[i] != '\0')
	{
		if (ft_strnstr(&s[i], old, ft_strlen(&s[i])) == &s[i])
		{
			idx = i;
			break;
		}
		i++;
	}
	result = (char*)malloc(ft_strlen(s) + (ft_strlen(new) - ft_strlen(old)) + 1);
	i = 0;
	j = 0;
	while (s[j])
	{
		if (j == idx)
		{
			strcpy(&result[i], new);
			i += ft_strlen(new);
			j += ft_strlen(old);
		}
		else
			result[i++] = s[j++];
	}
	result[i] = '\0';
	free(s);
	return result;
}

t_exp *ft_getidx(t_exp *exp, char *s)
{
	int i;
	t_exp *tmp;
	// int j;

	i = 0;
	tmp = exp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, s, ft_strlen(s)) == 0 && ft_strlen(s) == ft_strlen(tmp->var))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

char*	exp_and(t_exp *exp, char **env, char *s, int *j)
{
	int		k;
	char	*str;
	t_exp	*tmp;
	int 	i;

	(void)env;
	k = 0;
	i = *j;
	while (s[i] && ft_isvalid(s[i]))
	{
		i++;
		k++;
	}
	k++;
	if (k > 1) {
		str = ft_cpy(&s[i - k], k);
		tmp = ft_getidx(exp, str);
		if (tmp && k > -1) {
			s = ft_replace(s, str, tmp->value, j);
			i += ft_strlen(tmp->value) - ft_strlen(str);
		}
		else {
			s = ft_replace(s, str, "\0", j);
			i -= ft_strlen(str);
		}
		(*j) = i;
		free(str);
	}
	else
		(*j)++;
	return (s);
}

char*	special_vars(char* s, int c, int *k, t_envp * my_env)
{
	char*	str;
	int 	i;

	i = *k;
	if (c == '?')
	{
		str = ft_cpy(&s[i - 1], 2);
		// printf("----> str %s\n", str);
		s = ft_replace(s, str, ft_itoa(my_env->status), &i);
		// i++;
	}
	if (ft_isdigit(c))
	{
		str = ft_cpy(&s[i - 1], 2);
		// printf("----> str %s\n", str);
		if (c == 48)
			s = ft_replace(s, str, "minishell", &i);
		else
			s = ft_replace(s, str, "\0", &i);
		// i++;
	}
	*k = i;
	free(str);
	return (s);
}

void	free_exp(t_exp **exp)
{
	t_exp	*tmp;

	tmp = *exp;
	while (tmp)
	{
		free(tmp->var);
		free(tmp->value);
		tmp = tmp->next;
	}
	free(*exp);
}

char *ft_exp(char *s, t_exp *exp, t_envp *my_env, int count)
{
	int i = 0;
	char *str;
	// char *ss;

	i = count;
	str = NULL;
	while (s[i])
	{
		if (s[i] == '$')
		{
			while (s[i] == '$' && s[i])
				i++;
			if (s[i] == '\0')
				break ;
			if (ft_isdigit(s[i]) || s[i] == '?')
				s = special_vars(s, s[i], &i, my_env);
			else
				s = exp_and(exp, my_env->env, s, &i);
		}
		else
			i++;
	}
	free_exp(&exp);
	return (s);
}

char*	get_string(t_envp *my_env, char *s, int count)
{
	t_exp *exp;

	// for (int i = 0; my_env->env[i]; i++){
	// 	printf("%s\n", my_env->env[i]);
	// }
	if (s && !sea_rch(s, '$'))
		return s;
	if (!s)
		return (NULL);
	exp = NULL;
	exp = ft_getVar(my_env->env, exp);
	return (ft_exp(s, exp, my_env, count));
}