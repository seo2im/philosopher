#include "philosoper.h"

int eating(t_ph *philosoper)
{	
	pthread_mutex_lock(&philosoper->live);
	message(philosoper, EAT);
	usleep(philosoper->manager->eat_time * 1000);
	philosoper->dead_limit = ft_gettime() + philosoper->manager->dead_time;
	philosoper->eat_count++;
	pthread_mutex_unlock(&philosoper->live);
	return (1);
}