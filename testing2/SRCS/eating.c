/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:02:12 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 23:00:17 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	take_fork(t_ph *ph)
{
	pthread_mutex_lock(&ph->manager->fork_mutex[ph->left_fork]);
	message(ph, "take fork", FALSE);
	pthread_mutex_lock(&ph->manager->fork_mutex[ph->right_fork]);
	message(ph, "take fork", FALSE);
}

void	putoff_fork(t_ph *ph)
{
	message(ph, "is sleep", FALSE);
	pthread_mutex_unlock(&ph->manager->fork_mutex[ph->left_fork]);
	pthread_mutex_unlock(&ph->manager->fork_mutex[ph->right_fork]);
	ft_usleep(ph->manager->time_sleep * 1000);
}

void	eat(t_ph *ph)
{
	pthread_mutex_lock(&ph->ph_mutex);
	ph->is_eat = TRUE;
	ph->time_last_meal = ft_gettime();
	ph->time_dead_limit = ph->time_last_meal + ph->manager->time_dead;
	message(ph, "is eating", FALSE);
	ft_usleep(ph->manager->time_eat * 1000);
	ph->num_eat++;
	ph->is_eat = FALSE;
	pthread_mutex_unlock(&ph->ph_mutex);
	pthread_mutex_unlock(&ph->eat_mutex);
}
