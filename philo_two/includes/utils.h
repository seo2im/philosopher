#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include "error.h"

#define TRUE 1
#define FALSE 0

typedef int t_bool;

int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
long	ft_gettime(void);
int		ft_write(const char *str);
int		ft_writen(const char *str);
char	*ft_itoa(long i);
char	*ft_strdcat(char *s1, char *s2);

#endif