# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 12:36:19 by rarahhal          #+#    #+#              #
#    Updated: 2022/07/28 12:49:00 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS =  Mandatory/minishell.c \

LIBFT = Libft/......\

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)

$(NAME): $(OBJS) $(OBJS_L)
        $(CC) $(FLAGS) $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

clean:
        @rm -rf *.o
        @rm -f Libft/*.o

fclean: clean
        @rm -f $(NAME)

re: fclean
        @make all

.PHONY: all clean fclean re
