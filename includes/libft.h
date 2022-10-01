/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:35:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/10/01 23:05:27 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

// Library
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include "minishell.h"

# include <sys/types.h>
# include <sys/wait.h>

// Function
void		*ft_calloc(size_t count, size_t size);
char		**ft_realloc(char	**s);
char		*ft_d_realloc(char	*s);
size_t		ft_strlen(const char *s);
size_t		ft_d_strlen(char **s);
int			ft_non_tokenable(int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_randstring(size_t length);

#endif
