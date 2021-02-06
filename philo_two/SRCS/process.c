/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:24:38 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 20:26:51 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		eating(t_ph *ph)
{
	if (!ph->last_meal_time)
	{
		sem_post(ph->last_meal_sem);
		return (1);
	}
	gettimeofday(ph->last_meal_time, NULL);
	message(ph, "eating", ph->last_meal_time);
	ph->num_of_eat++;
	sem_post(ph->last_meal_sem);
	usleep(ph->info->eat_time * 1000); //TODO : get time of usleep during eating time;
	return (0);
}

int		eat_check(t_ph *ph)
{
	struct timeval	current;
	int				ret;
	
	gettimeofday(&current, NULL);
	sem_wait(ph->last_meal_sem);
	if (!ph->last_meal_time ||
		ft_time(&current) - ft_time(ph->last_meal_time) > ph->info->dead_time)
	{
		free(ph->last_meal_time);
		message(ph, "died", &current);
		ph->last_meal_time = NULL;
	}
	ret = eating(ph);
	sem_post(ph->forks);
	sem_post(ph->forks);
	return (ret);
}

int		eat(t_ph *ph)
{
	struct timeval	current;

	if (eat_check(ph) || ph->num_of_eat == ph->info->eat_must)
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "sleeping", &current);
	usleep(ph->info->sleep_time * 1000); //TODO : ft_usleep diff check;
	if (!ph->last_meal_time)
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "thinking", &current);
	return (0);
}

int		take_fork(t_ph *ph)
{
	struct timeval	current;

	if (!ph->last_meal_time)
		return (1);
	if (sem_wait(ph->eat_available))
		return (1);
	if (sem_wait(ph->forks))
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "take fork", &current);
	if (sem_wait(ph->forks))
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "take fork", &current);
	if (sem_post(ph->eat_available))
		return (1);
	return (0);
}

void	*routine(void *argv)
{
	t_ph	*ph;

	ph = (t_ph *)argv;
	while (!take_fork(ph) && !eat(ph))
		;
	return (NULL);
}

int		wait_process(t_manager *manager)
{
	int		c;
	int		num;
	t_ph	**phs;

	num = manager->info->eat_must;
	phs = manager->phs;
	while (phs && *phs)
	{
		c = ((unsigned int)(*phs)->num_of_eat < (unsigned int)num) ? 0 : c + 1;
		if (!((*phs)->last_meal_time) || !(*(phs + 1)))
			phs = ((*phs)->last_meal_time && c < manager->info->num_of_ph) ? manager->phs : NULL;
		else
			phs++;
	}
	c = 0;
	phs = manager->phs;
	while (c < manager->info->num_of_ph)
	{
		sem_wait((*phs)->last_meal_sem);
		c += !((*phs)->last_meal_time) ? 1 : !!((*phs)->last_meal_time = NULL) + 0;
		sem_post((*phs)->last_meal_sem);
		if (!(phs + 1) && c != manager->info->num_of_ph)
		{
			++phs;
			phs = !(c *= 0) ? manager->phs : NULL;
		}
	}
	return (0);
}

int		process(t_manager *manager)
{
	t_ph	**phs;
	int		i;

	if (gettimeofday(manager->info->start_time, NULL))
		return (ERROR);
	phs = manager->phs;
	i = -1;
	while (phs[++i])
	{
		if (!(phs[i]->info = copy_info(manager->info)))
			return (ERROR);	
		phs[i]->last_meal_time->tv_sec = phs[i]->info->start_time->tv_sec;
		phs[i]->last_meal_time->tv_usec = phs[i]->info->start_time->tv_usec;
		phs[i]->num_of_eat = 0;
		
		if (pthread_create(phs[i]->thread, NULL, &routine, phs[i]))
			return (ERROR);
	}
	return (wait_process(manager) ? ERROR : SUCCESS);
}
