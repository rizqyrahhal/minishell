# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rarahhal <rarahhal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/28 12:36:19 by rarahhal          #+#    #+#              #
#    Updated: 2022/08/05 14:51:09 by rarahhal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS =  Mandatory/minishell.c \
		pipex/Mandatory/pipex.c \
		pipex/Mandatory/childs.c \
		pipex/Mandatory/error.c \


LIBFT = Libft/libft/ft_split.c \
		Libft/libft/ft_strjoin.c \
		Libft/libft/ft_strlen.c \
		Libft/libft/ft_strncmp.c \
		Libft/libft/ft_strnstr.c \
		Libft/libft/ft_calloc.c \
		Libft/libft/ft_strchr.c \

OBJS = $(SRCS:.c=.o)
OBJS_L = $(LIBFT:.c=.o)

$(NAME): $(OBJS) $(OBJS_L)
	$(CC) -lreadline $(FLAGS) $(OBJS) $(OBJS_L) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf Mandatory/*.o
	@rm -rf pipex/Mandatory/*.o
	@rm -f Libft/libft/*.o
	@rm -f Libft/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean
	@make all

.PHONY: all clean fclean re
