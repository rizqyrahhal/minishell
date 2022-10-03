# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 17:12:13 by rarahhal          #+#    #+#              #
#    Updated: 2022/10/03 18:57:29 by lsemlali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

sig_remove_ctr_c = `stty -echoctl`
NAME = minishell
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = 	parsing/main.c \
		parsing/signals.c \
		parsing/lexer.c \
		parsing/lexer_help.c \
		parsing/collect_string.c \
		parsing/free.c \
		parsing/free2.c \
		parsing/token.c \
		parsing/tac.c \
		parsing/syntax_error.c \
		parsing/unclosed_quotes.c \
		parsing/here_doc.c \
		parsing/here_doc_helper.c \
		parsing/parser.c \
		parsing/rediriction.c \
		parsing/env.c \
		parsing/expanda.c \
		parsing/exp_tools.c \
		parsing/exp_tools2.c \
		parsing/execution.c \
		execution/tools/tools1.c \
        execution/tools/arr_tools.c \
        execution/tools/arr_tools2.c \
		execution/ex_main_tools.c \
        execution/execute.c \
		execution/execute_1.c \
        execution/execute_2.c \
        execution/ex_tools.c \
        execution/ex_tools2.c \
        execution/builtins/cd.c \
        execution/builtins/echo.c \
        execution/builtins/env.c \
        execution/builtins/exit.c \
        execution/builtins/export.c \
        execution/builtins/pwd.c \
        execution/builtins/unset.c \
        execution/builtins/builtins_tools.c \

LIBFT = parsing/libft/ft_calloc.c \
		parsing/libft/ft_realloc.c \
		parsing/libft/ft_strlen.c \
		parsing/libft/ft_non_tokenable.c \
		parsing/libft/ft_strjoin.c \
		parsing/libft/ft_strdup.c \
		parsing/libft/ft_strncmp.c \
		parsing/libft/linked_list.c \
		parsing/libft/ft_strnstr.c \
		parsing/libft/ft_randstring.c \

EXECUT_LIBFT = execution/execut_libft/ft_split.c \
		execution/execut_libft/ft_atoi.c \
		execution/execut_libft/ft_strcmp.c \
		execution/execut_libft/ft_strchr.c \
		execution/execut_libft/ft_strlcpy.c \
		execution/execut_libft/ft_isalpha.c \
		execution/execut_libft/ft_tolower.c \
		execution/execut_libft/ft_lower.c \
		execution/execut_libft/ft_isdigit.c \
		execution/execut_libft/ft_putstr_fd.c \
		execution/execut_libft/ft_itoa.c \
		execution/execut_libft/ft_substr.c

READLINE = ~/.brew/opt/readline

$(NAME):  $(SRCS) $(LIBFT) $(EXECUT_LIBFT)
	@echo "\033[0;34m                     -------------------------------\n                     | MINISHELL COMPILING ....... |\n                     -------------------------------\n\033[0m"
	@$(sig_remove_ctr_c)
	@$(CC) -lreadline -L $(READLINE)/lib -I $(READLINE)/include $(CFLAGS) $(SRCS) $(LIBFT) $(EXECUT_LIBFT) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)
	@rm -f /tmp/_????????

re: fclean
	@make all

.PHONY: all clean fclean re