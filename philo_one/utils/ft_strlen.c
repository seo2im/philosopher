#include "utils.h"

int ft_strlen(const char *str)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
		;
	return (i);
}