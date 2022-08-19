/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:12:03 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/19 14:31:18 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/lexer.h"
#include "../includes/tac.h"

int	main(int argc, char** argv, char** envp)
{
	char*	buf;

	if (argc > 1)
	{
		printf("error in argemment\n");
		return (0);
	}
	while(1)
	{
		buf = readline("\033[0;33m minishell >\033[0m");
		tac_compile(buf);
		free(buf);
	}

	return 0;
}
// < file ls -la | wc -l > file1


//  $ kudfhsk
// g e"c"'h'o
// "$HOME.fsdgs" OR "$HOME-fsdgs"
//  $USER.sgsrg  OR $USER-sgsrg
// 
// '$HOME'   hna ma3labalich bi $