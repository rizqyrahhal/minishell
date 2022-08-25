/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:35:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 04:02:53 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

// Library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include "../includes/struct.h"

// Function
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
int			ft_non_tokenable(int c);
t_command	*ft_lstnew(char *s, int infile, int outfile);
void		ft_addfront(t_command	**list, t_command *new);

#endif
