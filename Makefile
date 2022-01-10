# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsanche <alsanche@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 16:00:21 by alsanche          #+#    #+#              #
#    Updated: 2022/01/10 13:07:37 by alsanche         ###   ########lyon.fr    #
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
		$(CC) $^ -o $@ $(CFLAGS) $(DEBUG)

clean:
		make fclean -C ../Libft
		rm -rf $(OBJS)

fclean:
		rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean