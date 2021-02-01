#include "philosoper.h"

int eating(t_ph *philosoper)
{
	sem_wait(philosoper->live);
	philosoper->dead_limit = ft_gettime() + philosoper->manager->dead_time * 1000;
	message(philosoper, EAT);
	usleep(philosoper->manager->eat_time * 1000);
	philosoper->eat_count++;
	sem_post(philosoper->live);
}