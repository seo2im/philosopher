TARGET = philo_three
SRCS = ./srcs/*.c ./utils/*.c ./error/*.c
OBJS = *.o
CC = gcc
FLAG = -Wall -Werror -Wextra
HEADER = -I ./includes

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(SRCS) $(HEADER) -lpthread

$(OBJS) : $(SRCS)
	$(CC) -c $(SRCS) $(HEADER) -lpthread

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(TARGET)

