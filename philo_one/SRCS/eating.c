/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:57:33 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 16:29:51 by seolim           ###   ########.fr       */
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
	usleep(ph->info->eat_time * 1000);
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
	usleep(ph->info->sleep_time * 1000);
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
