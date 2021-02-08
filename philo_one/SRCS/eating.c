/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:02:12 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 19:47:28 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->fork_mutex[ph->left_fork]);
	message(ph, "take fork");
	pthread_mutex_lock(&ph->fork_mutex[ph->right_fork]);
	message(ph, "take fork");
}

void	putoff_fork(t_ph *ph)
{
	message(ph, "is sleep");
	pthread_mutex_lock(&ph->fork_mutex[ph->left_fork]);
	pthread_mutex_lock(&ph->fork_mutex[ph->right_fork]);
	ft_usleep(ph->info->time_sleep * 1000);
}

void	eat(t_ph *ph)
{
	pthread_mutex_lock(&ph->ph_mutex);
	ph->is_eat = 1;
	ph->time_last_meal = ft_gettime();
	ph->time_dead_limit = ph->time_last_meal + ph->info->start_time;
	message(ph, "is eating");
	ft_usleep(ph->info->time_eat * 1000);
	ph->num_eat++;
	ph->is_eat = FALSE;
	pthread_mutex_unlock(&ph->ph_mutex);
	pthread_mutex_unlock(&ph->eat_mutex);
}
