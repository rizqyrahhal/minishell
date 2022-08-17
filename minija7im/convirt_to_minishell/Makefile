# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/17 17:12:13 by rarahhal          #+#    #+#              #
#    Updated: 2022/08/17 17:39:58 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS = 	src/main.c \
		src/lexer.c \
		src/token.c \
		src/tac.c \

LIBFT = libft/ft_calloc.c \
		

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)

$(NAME): $(OBJS) $(OBJS_L)
	$(CC) -lreadline $(FLAGS) $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf src/*.o
	@rm -rf libft/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re
