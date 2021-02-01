#include "error.h"

int	ft_error(char *str, int code)
{
	int i;

	i = -1;
	while (str[++i])
		write(1, str + i, 1);
	write(1, "\n", 1);
	return (code);
}