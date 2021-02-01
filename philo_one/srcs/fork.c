/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:33:10 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:40:15 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

int	get_fork(t_ph *philosoper)
{
	pthread_mutex_lock(&philosoper->manager->forks[philosoper->left_fork]);
	if (philosoper->is_end)
	{
		pthread_mutex_unlock(
			&philosoper->manager->forks[philosoper->left_fork]);
		return (0);
	}
	message(philosoper, FORK);
	pthread_mutex_lock(&philosoper->manager->forks[philosoper->right_fork]);
	if (philosoper->is_end)
	{
		pthread_mutex_unlock(
			&philosoper->manager->forks[philosoper->left_fork]);
		pthread_mutex_unlock(
			&philosoper->manager->forks[philosoper->right_fork]);
		return (0);
	}
	message(philosoper, FORK);
	return (1);
}

int	put_fork(t_ph *philosoper)
{
	pthread_mutex_unlock(&philosoper->manager->forks[philosoper->left_fork]);
	pthread_mutex_unlock(&philosoper->manager->forks[philosoper->right_fork]);
	if (philosoper->is_end)
		return (0);
	message(philosoper, SLEEP);
	usleep(philosoper->manager->sleep_time * 1000);
	if (philosoper->is_end)
		return (0);
	message(philosoper, THINK);
	return (1);
}
