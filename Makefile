# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 17:12:13 by rarahhal          #+#    #+#              #
#    Updated: 2022/09/30 17:56:05 by lsemlali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

sig_remove_ctr_c = `stty -echoctl`
NAME = minishell
CFLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = 	src/main.c \
		src/lexer.c \
		src/lexer_help.c \
		src/collect_string.c \
		src/free.c \
		src/token.c \
		src/tac.c \
		src/syntax_error.c \
		src/unclosed_quotes.c \
		src/here_doc.c \
		src/here_doc_helper.c \
		src/parser.c \
		src/rediriction.c \
		src/env.c \
		src/expanda.c \
		src/exp_tools.c \
		src/exp_tools2.c \
		src/execution.c \
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

LIBFT = libft/ft_calloc.c \
		libft/ft_realloc.c \
		libft/ft_strlen.c \
		libft/ft_non_tokenable.c \
		libft/ft_strjoin.c \
		libft/ft_strdup.c \
		libft/ft_strncmp.c \
		libft/linked_list.c \
		libft/ft_strnstr.c \
		libft/ft_randstring.c \

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
	@$(sig_remove_ctr_c)
	@$(CC) -lreadline -g $(CFLAGS) $(SRCS) $(LIBFT) $(EXECUT_LIBFT) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)
	@rm -f /tmp/_????????

re: fclean
	@make all

.PHONY: all clean fclean re

# $(NAME):  $(SRCS) $(LIBFT) $(EXECUT_LIBFT)
# 	@echo "\033[0;34m                     -------------------------------\n                     | MINISHELL COMPILING ....... |\n                     -------------------------------\n\033[0m"
# 	@$(sig_remove_ctr_c)
# 	@$(CC) -lreadline -L $(READLINE)/lib -I $(READLINE)/include -g $(CFLAGS) $(SRCS) $(LIBFT) $(EXECUT_LIBFT) -o $(NAME)