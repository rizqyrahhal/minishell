# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 17:12:13 by rarahhal          #+#    #+#              #
#    Updated: 2022/09/10 18:27:05 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = 	src/main.c \
		src/lexer.c \
		src/token.c \
		src/tac.c \
		src/parser.c \
		src/env.c \
		src/expanda.c \
		src/execution.c \
		execution/tools/tools1.c \
        execution/tools/arr_tools.c \
        execution/tools/arr_tools2.c \
        execution/execute.c \
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

EXECUT_LIBFT = execut_libft/ft_split.c \
		execut_libft/ft_atoi.c \
		execut_libft/ft_strcmp.c \
		execut_libft/ft_strchr.c \
		execut_libft/ft_strlcpy.c \
		execut_libft/ft_isalpha.c \
		execut_libft/ft_isdigit.c \
		execut_libft/ft_putstr_fd.c \
		execut_libft/ft_itoa.c \
		execut_libft/ft_substr.c
		

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)
OBJS_EL = $(EXECUT_LIBFT:.c=.o)

$(NAME): $(OBJS) $(OBJS_L) $(EXECUT_LIBFT)
	$(CC) -lreadline $(FLAGS) $(OBJS) $(OBJS_L) $(EXECUT_LIBFT) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf src/*.o
	@rm -rf libft/*.o
	@rm -rf execut_libft/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re



# flageeeeeeeeeeeeeeeeeeeeeg
