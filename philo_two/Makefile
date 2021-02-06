NAME = philo_two
SRCS = ./SRCS/main.c \
		./SRCS/setup.c \
		./SRCS/message.c \
		./SRCS/process.c \
		./UTILS/ft_atoi.c \
		./UTILS/ft_error.c \
		./UTILS/ft_itoa.c \
		./UTILS/ft_strlen.c \
		./UTILS/ft_write.c \
		./UTILS/ft_write_n.c \
		./UTILS/ft_time.c \

		
OBJS = $(SRCS:.c=.o)
CC = gcc
FLAG = -Wall -Werror -Wextra
HEADER = -I ./HEADER

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(HEADER) -lpthread

$(OBJS) : %.o : %.c
	$(CC) -c $< -o $@ $(HEADER) > /dev/null

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all