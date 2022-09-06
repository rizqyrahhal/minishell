/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:10:22 by rarahhal          #+#    #+#             */
/*   Updated: 2022/09/06 17:55:27 by rarahhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <unistd.h>
#include <string.h>

#include "libft.h"

#define MAX(a, b)\
   a > b ? a : b

#define MIN(a, b)\
   a < b ? a : b

// ********************************************* token.h

typedef struct s_token
{
	char* value;
	enum
	{
		TOKEN_STRING, // cmd, argment, files, any other tokents ...
		TOKEN_PIPE, // | pipe
		// TOKEN_DQ, // " double qoute
		// TOKEN_SQ, // ' single qoute
		TOKEN_IN, // < inpute redirection
		TOKEN_HERDOC, // << her_doc
		TOKEN_OU, // > output redirection
		TOKEN_APPAND, // >> appandade output redirection
		TOKEN_R, // \n
		TOKEN_EOF, // \0 end of file
	} type;
} t_token;

t_token*	init_token(char* value, int type);
char*		token_to_str(t_token* token);


// ******************************************************** struct.h
typedef struct s_command_node
{
	char**	cmd;
	
	int		infile; // < if input != 0
	int		outfile; // > if output != 1
	char*	name_of_file; // last output file name
	struct s_command_node *next;
} t_command;

typedef struct s_envp
{
	char	**env; // hna fin ghanzido ila exporta chi variable bar realooc wola ghanm7iwh ila unseta
	int		*exit_status;
}	t_envp;

//************************************************* lexer.h

typedef struct s_lexer
{
	char*			src;
	size_t			src_size;
	char			c;
	unsigned int	i;
	t_token*		token;
	t_envp*			my_env;
} t_lexer;

t_lexer*	init_lexer(char* src);
void		lexer_advance(t_lexer* lexer);
void		lexer_skip_whitespace(t_lexer* lexer);
char		lexer_peek(t_lexer* lexer, int offset);
t_token*	lexer_advance_with(t_lexer* lexer, t_token* token);
t_token*	lexer_advance_current(t_lexer* lexer, int type);
t_token*	lexer_next_token(t_lexer* lexer);


void	fill_env(char *env[], t_envp *my_env);

// ************************************************ parser.h
typedef struct s_parser
{
	char**	cmd;
	int		infile;
	int		outfile;
	char	*name_of_file;
} t_parser;

t_command*	parser(t_lexer* lexer, t_token* token, t_command* list);

// *********************************************** tac.h
typedef struct s_tac
{
	t_lexer*	lexer;
	t_token*	token;
	t_command*	list;
	t_parser*	parser;
} t_tac;


void	tac_compile(char* src, t_envp* my_env);
void	print_node(t_command *lst);

// function of linked list
t_command*	ft_lstnew(char** s, int infile, int outfile);
void		ft_addfront(t_command** list, t_command* new);
#endif