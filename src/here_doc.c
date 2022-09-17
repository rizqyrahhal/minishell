/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/17 14:44:29 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char*	here_doc(char* src)
{
	int 	i;
	char*	str;
	int		j;
	char*	del_to_name;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	del_to_name = "file.txt\0";
	str = malloc(1);
	while(src && src[i])
	{
		if (src[i] == '<' && src[i + 1] == '<')
		{
			str = ft_d_realloc(str);
			str[j++] = src[i++];
			str = ft_d_realloc(str);
			str[j++] = src[i++];
			while ((src[i] == ' ' || src[i] == '\t') && src[i]){
				str = ft_d_realloc(str);
				str[j++] = src[i++];	
			}
			while (del_to_name && del_to_name[k])
			{
				str = ft_d_realloc(str);
				str[j++] = del_to_name[k++];
				if ((src[i] != ' ' && src[i] != '\t' && src[i] != '>' && src[i] != '<' && src[i] != '|') && src[i])//// adding non_tokenabel apres
					i++;
			}
		}
		else
		{
			str = ft_d_realloc(str);
			str[j++] = src[i++];
		}
		k = 0;
	}
	str[j] = '\0';
	return (str);
}
