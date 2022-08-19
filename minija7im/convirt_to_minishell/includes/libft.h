/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:35:14 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/19 03:51:37 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

// Library
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>

// Function
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
int		ft_isalpha(int c);
int		ft_isdigit(int c);

#endif
