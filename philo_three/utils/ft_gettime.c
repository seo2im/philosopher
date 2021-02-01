#include "utils.h"

long		ft_gettime(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((int)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}