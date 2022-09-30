/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:42:34 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/30 18:35:47 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*exp_and(t_exp *exp, char *s, int *j)
{
	int		k;
	t_exp	*tmp;

	exp->i = *j;
	k = sk_ip(exp, s);
	if (k > 1)
	{
		exp->str = ft_cpy(&s[exp->i - k], k);
		tmp = ft_getidx(exp, exp->str);
		if (tmp && k > -1)
		{
			s = ft_replace(s, exp->str, tmp->value, j);
			exp->i += ft_strlen(tmp->value) - ft_strlen(exp->str);
		}
		else
		{
			s = ft_replace(s, exp->str, "\0", j);
			exp->i -= ft_strlen(exp->str);
		}
		(*j) = exp->i;
		free(exp->str);
	}
	else
		(*j)++;
	return (s);
}

char	*special_vars(char *s, int c, int *k, t_envp *my_env)
{
	char	*str;
	int		i;

	i = *k;
	if (c == '?')
	{
		str = ft_cpy(&s[i - 1], 2);
		s = ft_replace(s, str, ft_itoa(my_env->status), &i);
	}
	if (ft_isdigit(c))
	{
		str = ft_cpy(&s[i - 1], 2);
		if (c == 48)
			s = ft_replace(s, str, "minishell", &i);
		else
			s = ft_replace(s, str, "\0", &i);
	}
	*k = i;
	free(str);
	return (s);
}

void	free_exp(t_exp **exp)
{
	t_exp	*tmp;
	t_exp	*tmp2;

	tmp = *exp;
	while (tmp)
	{
		free(tmp->var);
		free(tmp->value);
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

char	*ft_exp(char *s, t_exp *exp, t_envp *my_env, int count)
{
	int		i;

	i = 0;
	i = count;
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
				s = exp_and(exp, s, &i);
		}
		else
			i++;
	}
	free_exp(&exp);
	return (s);
}

char	*get_string(t_envp *my_env, char *s, int count)
{
	t_exp	*exp;
	char	*str;

	if (s && !sea_rch(s, '$'))
	{
		str = ft_strdup(s);
		free(s);
		return (str);
	}
	if (!s)
		return (NULL);
	exp = NULL;
	exp = ft_getvar(my_env->env, exp);
	return (ft_exp(s, exp, my_env, count));
}
