/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:33:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/28 16:09:36 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execution.h"

char	*ft_cpy(char *s, int k)
{
	char	*var;
	int		i;

	i = 0;
	var = malloc(k + 1);
	while (i < k)
	{
		var[i] = s[i];
		i++;
	}
	var[i] = 0;
	return (var);
}

void	fill_env(char *env[], t_envp *my_env)
{
	int	i;
	int	k;

	k = arr_s(env, "OLDPWD");
	if (k == -1)
		my_env->env = (char **)malloc(sizeof(char *) * (ft_d_strlen(env) + 2));
	else
		my_env->env = (char **)malloc(sizeof(char *) * (ft_d_strlen(env) + 1));
	i = 0;
	while (env[i])
	{
		if (k == -1 && i == 8)
			my_env->env[i] = ft_strdup("OLDPWD");
		else
			my_env->env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env->env[i] = 0;
}

