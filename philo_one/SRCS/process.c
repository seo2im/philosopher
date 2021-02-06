/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:24:38 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 17:03:24 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		eating(t_ph *ph)
{
	if (!ph->last_meal_time)
	{
		pthread_mutex_unlock(ph->last_meal_mutex);
		return (1);
	}
	gettimeofday(ph->last_meal_time, NULL);
	message(ph, "eating", ph->last_meal_time);
	ph->num_of_eat++;
	usleep(ph->info->eat_time * 1000); //TODO : get time of usleep during eating time;
	pthread_mutex_unlock(ph->last_meal_mutex);
	return (0);
}

int		eat_check(t_ph *ph)
{
	struct timeval	current;
	int				ret;
	
	gettimeofday(&current, NULL);
	pthread_mutex_lock(ph->last_meal_mutex);
	if (!ph->last_meal_time ||
		ft_time(&current) - ft_time(ph->last_meal_time) > ph->info->dead_time)
	{
		free(ph->last_meal_time);
		message(ph, "died", &current);
		ph->last_meal_time = NULL;
	}
	ret = eating(ph);
	pthread_mutex_unlock(ph->right_fork->mutex);
	pthread_mutex_unlock(ph->left_fork->mutex);
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
	t_fork			*fork;
	int				i;
	struct timeval	current;

	if (!ph->last_meal_time)
		return (1);
	fork = (ph->id % 2) ? ph->left_fork : ph->right_fork;
	i = 0;
	while (i < 2)
	{
		if (fork->nb_last != ph->id)
		{
			pthread_mutex_lock(fork->mutex);
			gettimeofday(&current, NULL);
			message(ph, "take fork", &current);
			fork->nb_last = ph->id;
			if (++i != 2)
				fork = (ph->id + i) % 2 ? ph->left_fork : ph->right_fork;
		}
	}
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
	while (phs && *phs && !usleep(1000))
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
		pthread_mutex_lock((*phs)->last_meal_mutex);
		c += !((*phs)->last_meal_time) ? 1 : !!((*phs)->last_meal_time = NULL) + 0;
		pthread_mutex_unlock((*phs)->last_meal_mutex);
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
