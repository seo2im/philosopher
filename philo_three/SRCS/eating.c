/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:38:10 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:38:28 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		eating(t_ph *ph)
{
	if (!ph->last_meal_time)
		return (1);
	gettimeofday(ph->last_meal_time, NULL);
	message(ph, "eating", ph->last_meal_time);
	ph->num_of_eat++;
	usleep(ph->info->eat_time * 1000);
	return (0);
}

int		eat_check(t_ph *ph)
{
	struct timeval	current;
	int				ret;
	
	gettimeofday(&current, NULL);
	if (!ph->last_meal_time ||
		ft_time(&current) - ft_time(ph->last_meal_time) > ph->info->dead_time)
	{
		free(ph->last_meal_time);
		message(ph, "died", &current);
		ph->last_meal_time = NULL;
		ret = -1;
	}
	else
		ret = eating(ph);
	sem_post(ph->forks);
	sem_post(ph->forks);
	sem_post(ph->eat_available);
	return (ret);
}

int		eat(t_ph *ph)
{
	struct timeval	current;

	if (eat_check(ph))
		return (-1);
	if (ph->num_of_eat == ph->info->eat_must)
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