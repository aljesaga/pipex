NAME  = libft.a

SRC	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c\
    ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
    ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c\
    ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c\
    ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c\
    ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c\
    ft_toupper.c ft_strtrim.c ft_split.c ft_itoa.c \
    ft_putchar_fd.c ft_putstr_fd.c ft_strmapi.c \
    ft_striteri.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_B = ft_lstnew_bonus.c ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c

OBJS = $(SRC:.c=.o)

OBJS_B = $(SRC_B:.c=.o)

CC	= gcc

AR = ar rcs

RM 	= rm -f

CFLAGS	= -Wall -Wextra -Werror -pedantic

$(NAME): $(OBJS)
	@ar r $(NAME) $(OBJS)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

bonus: $(OBJS_B)
		$(AR) $(NAME) $^

clean:	
	@rm -f $(OBJS) $(OBJS_B)

fclean:	clean
	@rm -f $(NAME)

re: fclean all

PHONY.:clean all fclean bonus re 
