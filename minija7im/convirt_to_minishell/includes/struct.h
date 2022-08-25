/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:53:58 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/25 17:48:31 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H


// static struct variables
// {
// 	/* data */
// 	int exit_status;
// };

// static int exit_status;

typedef struct s_command_node
{
	char*	cmd;
	int		infile; // < if input != 0
	int		outfile; // > if output != 1
	struct s_command_node *next;
} t_command;

typedef struct s_envp
{
	char	**env; // hna fin ghanzido ila exporta chi variable bar realooc wola ghanm7iwh ila unseta
	int		*exit_status;
}	t_envp;

#endif