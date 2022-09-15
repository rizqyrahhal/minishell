/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:33:47 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/15 17:18:10 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


char    *ft_cpy(char *s, int k)
{
	char    *var;
	int     i;
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
	int i;

	i = 0;
	while (env[i])
	{
		my_env->env[i] = ft_cpy(env[i], ft_strlen(env[i]));
		i++;
	}
	my_env->env[i] = 0;
}