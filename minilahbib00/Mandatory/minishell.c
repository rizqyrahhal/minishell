/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 12:42:37 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/20 10:34:45 by lsemlali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/minishell.h"

int ft_exp(char **s)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (s[i])
    {
        while (s[i][j])
        {
            if (s[i][j] == '$')
            {

            }
        }
    }
}

int env_size(char *env[])
{
    int i;

    i = 0;
    while (env[i])
        i++;
    return (i);
}

char    *ft_cpy(char *s, int k)
{
    char    *var;
    int     i;
    i = 0;
    var = malloc(k + 1);
    var[k] = 0;
    while (i < k)
    {
        var[i] = s[i];
        i++;
    }
    return (var);
}

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
        (*exp)[k].var = ft_cpy(env[i], j++);
        (*exp)[k].value = ft_cpy(&env[i][j], ft_strlen(&env[i][j]));
        j = 0;
        i++;
        k++;
    }
}

int	sea_rrch(char *s, int a)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (1);
		i++;
	}
	return (0);
}

int	ft_countt(char *s, int a)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		if (s[i] == a)
			count++;
		i++;
	}
	return (count);
}

int	main(int ac, char *av[], char *env[])
{
	t_command	*command;
    t_exp *exp;
	char		**s;
	char		*buf;
	int			k;
	int			i;
	
	k = 0;
	i = 0;
	command = malloc(sizeof(t_command));
	exp = malloc(sizeof(t_exp) * env_size(env));
    ft_getVar(env, &exp);
	// printf("%s\n %s\n %s\n %s\n",command[0].arry[0], command[0].arry[1], command[1].arry[0], command[1].arry[1]);
	while(1)
	{
		buf = readline("\033[0;33m minishell > \033[0m");
		k = ft_countt(buf, '|');
		//command->arry = ft_split(buf, '|');
		if (k >= 1)
		{
			//s = ft_split(buf, '|');
			command->arry = ft_split(buf, '|');
			// if (ft_strncmp(s))
			if (k > 1)
				mpipex(k, command->arry, env);
			else
				dpipex(ac, command->arry, env);
			free(command->arry);
		}
		else
			pipex(ac, buf, env);
		free(buf);
	}
	return (0);
}
