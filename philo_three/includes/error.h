#ifndef ERROR_H
# define ERROR_H
# include <unistd.h>

#define SUCCESS 1
#define FAIL 0
#define ERROR -1
int	ft_error(char *str, int code);

#endif