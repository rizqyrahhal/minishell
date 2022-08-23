/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 12:53:58 by rarahhal          #+#    #+#             */
/*   Updated: 2022/08/23 15:26:25 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef struct s_command_node
{
	char*	cmd;
	int		input; // < if input != 0
	int		output; // > if output != 1
	struct s_command_node *next;
} t_command;

typedef struct s_envp
{
	char	**env; // hna fin ghanzido ila exporta chi variable bar realooc wola ghanm7iwh ila unseta
	int		*exit_status;
}	t_envp;

#endif