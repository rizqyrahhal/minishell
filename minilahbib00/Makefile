# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsemlali <lsemlali@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 12:36:19 by rarahhal          #+#    #+#              #
#    Updated: 2022/08/07 21:32:54 by lsemlali         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra -ILibft/libft
CC = cc

SRCS =  Mandatory/minishell.c \
		Mandatory/expanda.c \
		tools/tools1.c \
		tools/arr_tools.c \
		tools/arr_tools2.c \
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
		execution/put_error.c \

LIBFT = Libft/libft/ft_split.c \
		Libft/libft/ft_strjoin.c \
		Libft/libft/ft_atoi.c \
		Libft/libft/ft_strlen.c \
		Libft/libft/ft_strncmp.c \
		Libft/libft/ft_strcmp.c \
		Libft/libft/ft_strnstr.c \
		Libft/libft/ft_strchr.c \
		Libft/libft/ft_strdup.c \
		Libft/libft/ft_strlcpy.c \
		Libft/libft/ft_isalpha.c \
		Libft/libft/ft_isdigit.c \
		Libft/libft/ft_putstr_fd.c \
		Libft/libft/linked_list.c \
		Libft/libft/ft_substr.c

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)

$(NAME): $(OBJS) $(OBJS_L)
	$(CC) -lreadline $(FLAGS) $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) -ILibft/libft -c $< -o $@

clean:
	@rm -rf Mandatory/*.o
	@rm -rf execution/*.o
	@rm -rf execution/builtins/*.o
	@rm -f Libft/libft/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re
