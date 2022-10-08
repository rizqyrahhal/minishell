/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 16:19:01 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/08 14:13:31 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	check_export(char *var)
{
	int	i;
	int	k;

	k = 0;
	while (var[k] && var[k] != '=')
		k++;
	if (var[k - 1] == '+' && var[k] == '\0')
		return (0);
	if (var[k - 1] == '+')
		k--;
	i = 0;
	if (ft_isdigit(var[0]) || !ft_isvalid(var[0]))
		return (0);
	while (i < k)
	{
		if (!ft_isvalid(var[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ex_export(char **sp, t_envp *my_env, int out)
{
	int		i;

	i = 1;
	if (sp[1] == NULL)
		export_(my_env->env, out);
	while (sp[i])
	{
		if (sp[1][0] == '-')
		{
			putstr_fd("options not required\n", 2);
			my_env->status = 2;
			return ;
		}
		if (i > 1 && my_env->status != 1)
			my_env->status = ft_add2env(my_env, sp[i]);
		else if (i == 1)
			my_env->status = ft_add2env(my_env, sp[i]);
		i++;
	}
}
