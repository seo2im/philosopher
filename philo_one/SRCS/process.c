/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:23:32 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 19:47:02 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*check(void *argv)
{
	t_ph	*ph;

	ph = (t_ph *)argv;
	while (TRUE)
	{
		pthread_mutex_lock(&ph->ph_mutex);
		if (!ph->is_eat && ft_gettime() < ph->time_dead_limit)
		{
			message(ph, "is died");
			pthread_mutex_unlock(&ph->ph_mutex);
			pthread_mutex_unlock(&ph->dead_mutex);
			return ((void *)0);
		}
		pthread_mutex_unlock(&ph->ph_mutex);
		usleep(50);
	}
}

static void	*routine(void *argv)
{
	t_ph		*ph;
	pthread_t	tid;

	ph = (t_ph *)argv;
	ph->time_last_meal = ft_gettime();
	ph->time_dead_limit = ph->time_last_meal + ph->info->time_dead;
	if (pthread_create(&tid, NULL, &check, ph))
		return ((void *)1);
	while (TRUE)
	{
		take_fork(ph);
		eat(ph);
		putoff_fork(ph);
		message(ph, "is Thinking");
	}
	return ((void *)0);
}

int		process(t_manager *manager)
{
	int			i;
	pthread_t	tid;
	void		*ph;

	manager->info->start_time = ft_gettime();
	
	i = -1;
	while (manager->phs[++i])
	{
		ph = manager->phs[i];
		if (pthread_create(&tid, NULL, &routine, ph))
			return (ERROR);
		pthread_detach(tid);
		usleep(50);
	}
	return (SUCCESS);
}
