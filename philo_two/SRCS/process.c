/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:23:32 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 14:03:27 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*eat_check(void *argv)
{
	t_manager	*manager;
	int			i;

	manager = (t_manager *)argv;
	while (manager->info->cur_eat_count < manager->info->num_eat)
	{
		i = -1;
		while (++i < manager->info->num_of_ph)
			sem_wait(manager->phs[i].eat_sem);
		manager->info->cur_eat_count++;
	}
	message(&manager->phs[0], "Process Over", FALSE, TRUE);
	sem_post(manager->info->dead_sem);
	return ((void *)0);
}

static void	*check(void *argv)
{
	t_ph	*ph;

	ph = (t_ph *)argv;
	while (TRUE)
	{
		sem_wait(ph->ph_sem);
		if (!ph->is_eat && ft_gettime() > ph->time_dead_limit)
		{
			message(ph, "is died", TRUE, FALSE);
			sem_post(ph->ph_sem);
			sem_post(ph->info->dead_sem);
			return ((void *)0);
		}
		sem_post(ph->ph_sem);
		usleep(1000);
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
	pthread_detach(tid);
	while (TRUE)
	{
		take_fork(ph);
		eat(ph);
		putoff_fork(ph);
		message(ph, "is Thinking", FALSE, FALSE);
	}
	return ((void *)0);
}

int			process(t_manager *manager)
{
	int			i;
	pthread_t	tid;

	manager->info->start_time = ft_gettime();
	if (manager->info->num_eat > 0)
	{
		if (pthread_create(&tid, NULL, &eat_check, manager))
			return (ERROR);
		pthread_detach(tid);
	}
	i = -1;
	while (++i < manager->info->num_of_ph)
	{
		if (pthread_create(&tid, NULL, &routine, &manager->phs[i]))
			return (ERROR);
		pthread_detach(tid);
		usleep(100);
	}
	return (SUCCESS);
}
