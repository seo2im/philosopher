/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:24:38 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:16:10 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void			*routine(void *argv)
{
	t_ph	*ph;

	ph = (t_ph *)argv;
	while (!take_fork(ph) && !eat(ph))
		;
	return (NULL);
}

static	void	mutex_locking(t_manager *manager)
{
	int		c;
	t_ph	**phs;

	c = 0;
	phs = manager->phs;
	while (c < manager->info->num_of_ph)
	{
		pthread_mutex_lock((*phs)->last_meal_mutex);
		c += !((*phs)->last_meal_time) ? 1 :
				!!((*phs)->last_meal_time = NULL) + 0;
		pthread_mutex_unlock((*phs)->last_meal_mutex);
		if (!(phs + 1) && c != manager->info->num_of_ph)
		{
			++phs;
			phs = !(c *= 0) ? manager->phs : NULL;
		}
	}	
}

int				wait_process(t_manager *manager)
{
	int		c;
	int		num;
	t_ph	**phs;

	num = manager->info->eat_must;
	phs = manager->phs;
	while (phs && *phs && !usleep(1000))
	{
		c = ((unsigned int)(*phs)->num_of_eat < (unsigned int)num) ? 0 : c + 1;
		if (!((*phs)->last_meal_time) || !(*(phs + 1)))
			phs = ((*phs)->last_meal_time && c < manager->info->num_of_ph)
			? manager->phs : NULL;
		else
			phs++;
	}
	mutex_locking(manager);
	return (0);
}

int				process(t_manager *manager)
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
		phs[i]->left_fork->nb_last = 0;
		phs[i]->right_fork->nb_last = 0;
		phs[i]->last_meal_time->tv_sec = phs[i]->info->start_time->tv_sec;
		phs[i]->last_meal_time->tv_usec = phs[i]->info->start_time->tv_usec;
		phs[i]->num_of_eat = 0;
		if (pthread_mutex_init(phs[i]->last_meal_mutex, NULL))
			return (ERROR);
		if (pthread_create(phs[i]->thread, NULL, &routine, phs[i]))
			return (ERROR);
	}
	return (wait_process(manager) ? ERROR : SUCCESS);
}
