#include "../includes/libft.h"
#include "../includes/tac.h"

typedef struct s_exp
{
	char	*var;
	char    *value;// alloca nmbr of command
}   t_exp;

void ft_getVar(char *env[], t_exp **exp)
{
	int i;
	int j;
	int k;

	k = 0;
	j = 0;
	i = 0;
	while (env[i])
	{
		while (env[i][j] != '=')
			j++;
		(*exp)[k].var = ft_strjoin("$", ft_cpy(env[i], j++));
		(*exp)[k].value = ft_cpy(&env[i][j], ft_strlen(&env[i][j]));
		j = 0;
		i++;
		k++;
	}
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

char* ft_replace(char* s, char* old, char* new)
{
	char*	result;
	int 	i;
	int		count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strnstr(&s[i], old, ft_strlen(&s[i])) == &s[i])
		{
			count++;
			i += ft_strlen(old) - 1;
		}
		i++;
	}
	result = (char*)malloc(i + count * (ft_strlen(new) - ft_strlen(old)) + 1);
	i = 0;
	while (*s)
	{
		if (ft_strnstr(s, old, ft_strlen(s)) == s)
		{
			strcpy(&result[i], new);
			i += ft_strlen(new);
			s += ft_strlen(old);
		}
		else
			result[i++] = *s++;
	}
	result[i] = '\0';
	return result;
}

int ft_getidx(t_exp *exp, char *s, char *env[])
{
	int i;
	int j;

	i = 0;
	while (i < arr_size(env))
	{
		if (ft_strncmp(exp[i].var, s, ft_strlen(s)) == 0 && ft_strlen(s) == ft_strlen(exp[i].var))
			return (i);
		i++;
	}
	return (-1);
}

char*	exp_and(t_exp *exp, char **env, char *s, int *j)
{
	int		k;
	char	*str;
	int 	i;

	k = 0;
	i = *j;
	while (s[i] == '$')
		i++;
	while (s[i] && ft_isvalid(s[i]))
	{
		i++;
		k++;
	}
	k++;
	if (k > 1) {
		str = ft_cpy(&s[i - k], k);
		k = ft_getidx(exp, str, env);
		if (k > -1) {
			s = ft_replace(s, str, exp[k].value);
			i += ft_strlen(exp[k].value) - ft_strlen(str);
		}
		else {
			s = ft_replace(s, str, "\0");
			i -= ft_strlen(str);
		}
	}
	*j = i;
	printf("+++%s\n", str);
	return (s);
}

char *ft_exp(char *s, t_exp *exp, char *env[])
{
	int i = 0;
	char *str;
	char *ss;
	int k;

//    i = 0;
	k = 0;
	str = NULL;
	while (s[i])
	{
		k = 0;
		if (s[i] == '$')
		{
			s = exp_and(exp, env, s, &i);
		}
		if (s[i] != '$')
			i++;
	}
	return (s);
}

void	get_string(char **env, char *s)
{
	t_exp *exp;

	exp = malloc((ft_d_strlen(env) + 1) * sizeof (t_exp));
	ft_getVar(env, &exp);
	ft_exp(s, exp, env);
}