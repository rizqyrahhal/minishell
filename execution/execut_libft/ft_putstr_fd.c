/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:22:57 by lsemlali          #+#    #+#             */
/*   Updated: 2022/10/02 09:58:35 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_libft.h"

void	putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
