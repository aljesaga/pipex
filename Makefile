# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 16:00:21 by alsanche          #+#    #+#              #
#    Updated: 2022/05/14 17:23:53 by alsanche         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = main.c send_error.c

OBJS =  $(SRCS:%.c=%.o)

CC = gcc

DEBUG = -fsanitize=address -g3

CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJS)
		make -sC ./Libft
		$(CC) $^ -o $@ $(CFLAGS) $(DEBUG) ./Libft/libft.a

clean:
		make clean -C ./Libft
		rm -rf $(OBJS)

fclean:
		make fclean -C ./Libft
		rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean