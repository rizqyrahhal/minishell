/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:18:52 by lsemlali          #+#    #+#             */
/*   Updated: 2022/09/25 16:18:53 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	*new_var(char *var)
{
	char	*new_var;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(var);
	while (var[i] && var[i] != '=')
		i++;
	if (var[i - 1] == '+')
		j--;
	new_var = malloc(j + 1);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '+')
			i++;
		new_var[j] = var[i];
		j++;
		i++;
	}
	new_var[j] = 0;
	return (new_var);
}

char	*new_value(char *s, char *old)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!sea_rch(old, '='))
		return (ft_substr(s, i, ft_strlen(s) - i));
	return (ft_substr(s, i + 1, ft_strlen(s) - i - 1));
}

char	*get_wich(char *old, char *new)
{
	int	i;

	i = 0;
	if (sea_rch(new, '='))
	{
		while (new[i] && new[i] != '=')
			i++;
		if (new[i - 1] == '+' && new[i + 1])
			return (ft_strjoin(old, new_value(new, old)));
		else if (new[i - 1] == '+' && !new[i + 1])
		{
			if (sea_rch(old, '='))
				return (ft_strdup(old));
			else
				return (new_var(new));
		}
		return (ft_strdup(new));
	}
	else
		return (old);
}

int	ft_add2env(t_envp *my_env, char *var)
{
	int	k;
	int	i;

	i = 0;
	if (!check_export(var))
	{
		var = ft_strjoin("minishell: export: `%s", var);
		var = ft_strjoin(var, "': not a valid identifier\n");
		putstr_fd(var, 2);
		return (1);
	}
	k = arr_s(my_env->env, var);
	if (k != -1)
		my_env->env[k] = get_wich(my_env->env[k], var);
	else
		arr_cpy(my_env, new_var(var));
	return (0);
}

int	ft_remove(t_envp *my_env, char *var)
{
	int		k;
	char	**s;

	if (!check_unset(var))
	{
		printf("minishell: unset: `%s': not a valid identifier\n", var);
		return (1);
	}
	if (arr_s(my_env->env, var) == -1)
		return (0);
	k = arr_size(my_env->env);
	s = malloc(k * sizeof (char *));
	arr_delete(my_env, s, var);
	my_env->env = s;
	return (0);
}
