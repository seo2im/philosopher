NAME = philo_one
SRCS = ./SRCS/main.c \
		./SRCS/setup.c \
		./SRCS/message.c \
		./SRCS/process.c \
		./SRCS/eating.c \
		./SRCS/setup_forks.c \
		./SRCS/setup_philosophers.c \
		./SRCS/clear.c \
		./UTILS/ft_atoi.c \
		./UTILS/ft_error.c \
		./UTILS/ft_itoa.c \
		./UTILS/ft_strlen.c \
		./UTILS/ft_write.c \
		./UTILS/ft_write_n.c \
		./UTILS/ft_time.c \
		./UTILS/ft_usleep.c \

		
OBJS = $(SRCS:.c=.o)
CC = gcc
FLAG = -Wall -Werror -Wextra
HEADER = -I ./HEADER

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAG) -o $(NAME) $(OBJS) $(HEADER) -lpthread

$(OBJS) : %.o : %.c
	$(CC) $(FLAG) -c $< -o $@ $(HEADER) > /dev/null

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all