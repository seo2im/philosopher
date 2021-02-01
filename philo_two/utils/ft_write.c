#include "utils.h"

int		ft_write(const char *str)
{
	int len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);	
	return (len);
}

int		ft_writen(const char *str)
{
	int len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);	
	write(1, "\n", 1);
	return (len + 1);
}