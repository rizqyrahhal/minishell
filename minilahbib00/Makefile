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
FLAGS = -Wall -Werror -Wextra
CC = cc

SRCS =  Mandatory/minishell.c \
		pipe/pipex.c \
		pipe/pipex_bonus.c \
		pipe/pipex_outils.c \
		pipe/pipex_outils2.c \
		pipe/put_error.c \


LIBFT = Libft/libft/ft_split.c \
		Libft/libft/ft_strjoin.c \
		Libft/libft/ft_strlen.c \
		Libft/libft/ft_strncmp.c \
		Libft/libft/ft_strnstr.c \
		Libft/libft/ft_strchr.c \
		Libft/libft/ft_strdup.c \
		Libft/libft/ft_strlcpy.c \
		pipe/lbft/ft_substr.c

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
