/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:29:43 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/18 19:55:24 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char*	here_doc(char* src, int stop)
{
	int 	i;
	char*	str;
	int		j;
	char*	del_to_name;
	int		k;
	int		fd;
	char*	here_doc;
	char*	delemeter;
	int		l;

	i = 0;
	j = 0;
	// del_to_name = NULL;
	str = malloc(1);
	str[0] = 0;
	here_doc = NULL;
	while(src && src[i])
	{
		k = 0;
		l = 0;
		delemeter = malloc(1);
		if (src[i] == '<' && src[i + 1] == '<')
		{
			str = ft_d_realloc(str);
			str = ft_d_realloc(str);
			str[j++] = src[i++];
			str[j++] = src[i++];
			str[j] = '\0';
			while ((src[i] == ' ' || src[i] == '\t') && src[i]){
				str = ft_d_realloc(str);
				str[j++] = src[i++];
				str[j] = '\0';	
			}
			


			del_to_name = ft_randstring(8);
			fd = open(del_to_name, O_CREAT | O_RDWR | O_TRUNC, 0644);



			while (del_to_name && del_to_name[k])
			{
				str = ft_d_realloc(str);
				str[j++] = del_to_name[k++];
				str[j] = '\0';
			}
			while ((src[i] != ' ' && src[i] != '\t' && src[i] != '>' && src[i] != '<' && src[i] != '|') && src[i] && i < stop)//// adding non_tokenabel apres
			{//// ghankhadame lexer ghi bach njib delemeter awla n7awol lojik dyal single qoute wo double qoute hna
				delemeter = ft_d_realloc(delemeter);
				delemeter[l++] = src[i++];
				delemeter[l] = '\0';
			}
			while (1)
			{
				here_doc = readline("> ");
				if (!here_doc || !ft_strncmp(delemeter, here_doc, ft_strlen(delemeter) + 1))
					break ;
				write(fd, here_doc, ft_strlen(here_doc));
				write(fd, "\n", 1);
				free(here_doc);
			}
			free(here_doc);
			fd = open(del_to_name, O_RDONLY, 0600);
			if (fd < 0)
			{
				unlink(del_to_name);
				printf("ERR_heredoc_infile\n");
			}
			close(fd);


			
		}
		else
		{
			str = ft_d_realloc(str);
			str[j++] = src[i++];
			str[j] = '\0';
		}
		free(delemeter);
	}
	str[j] = '\0';
	return (str);
}
