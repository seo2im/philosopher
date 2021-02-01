NAME = philo_one
SRCS = ./srcs/eating.c \
		./srcs/fork.c \
		./srcs/message.c \
		./srcs/philosopher.c \
		./utils/ft_atoi.c \
		./utils/ft_gettime.c \
		./utils/ft_itoa.c \
		./utils/ft_strlen.c \
		./utils/ft_write.c \
		./error/ft_error.c \
		./srcs/main.c

OBJS = $(SRCS:.c=.o)
CC = gcc
FLAG = -Wall -Werror -Wextra
HEADER = -I ./includes

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAG) -o $(NAME) $(OBJS) $(HEADER) -lpthread

$(OBJS) : %.o : %.c
	$(CC) $(FLAG) -c $< -o $@ $(HEADER) > /dev/null

clean :
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all
