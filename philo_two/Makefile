NAME = philo_two
HEADER = -I ./HEADER/
SRC = ./main.c \
        ./SRCS/setup.c \
        ./SRCS/process.c \
        ./SRCS/eating.c \
        ./SRCS/message.c \
        ./UTILS/ft_atoi.c \
        ./UTILS/ft_strlen.c \
        ./UTILS/ft_write.c \
        ./UTILS/ft_write_n.c \
        ./UTILS/ft_gettime.c \
        ./UTILS/ft_usleep.c \
        ./UTILS/ft_itoa.c \
        ./UTILS/sem_name.c

OBJS 		=	$(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra

all : $(NAME)

$(NAME) : $(OBJS)
	gcc $(FLAG) -o $(NAME) $(OBJS) $(HEADER) -lpthread

$(OBJS) : %.o : %.c
	gcc $(FLAG) -c $< -o $@ $(HEADER)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all


