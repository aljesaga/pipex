# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alsanche <alsanche@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/27 16:00:21 by alsanche          #+#    #+#              #
#    Updated: 2022/05/30 18:15:43 by alsanche         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ./src/main.c ./src/send_error.c ./src/ft_split.c ./src/pipex_utils.c

SRCS_BONUS = ./bonus/main_bonus.c ./bonus/send_error_bonus.c \
				./src/ft_split.c ./bonus/pipex_utils_2_bonus.c \
				./bonus/pipex_utils_bonus.c ./bonus/get_next_line.c \
				./bonus/get_next_line_utils.c

OBJS =  $(SRCS:%.c=%.o)

OBJS_BONUS = $(SRCS_BONUS:%.c=%.o)

CC = gcc

DEBUG = -fsanitize=address -g3

CFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $^ -o $@ $(CFLAGS) $(DEBUG)

bonus: $(OBJS_BONUS)
		$(CC) $(OBJS_BONUS) -o $(NAME) $(CFLAGS) $(DEBUG)

clean:
	@	rm -rf ./src/$(OBJS)
	@	rm -rf ./bonus/$(OBJS_BONUS) 

fclean:
	@	rm -f $(NAME)

re: fclean all

.PHONY: all re clean bonus fclean 