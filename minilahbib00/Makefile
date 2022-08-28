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
		pipes/pipex_bonus.c \
        pipes/here_doc.c \
        pipes/pipex_outils.c \
        pipes/pipex_outils2.c \
        pipes/put_error.c \
		pipes/get_next_line/get_next_line.c \
		pipes/get_next_line/get_next_line_utils.c \

LIBFT = Libft/libft/ft_split.c \
		Libft/libft/ft_strjoin.c \
		Libft/libft/ft_strlen.c \
		Libft/libft/ft_strncmp.c \
		Libft/libft/ft_strnstr.c \
		Libft/libft/ft_strchr.c \
		Libft/libft/ft_strdup.c \
		Libft/libft/ft_strlcpy.c \
		Libft/libft/ft_isalpha.c \
		Libft/libft/ft_putstr_fd.c \
		Libft/libft/linked_list.c \
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
