/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:46:49 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:47:00 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

int	get_fork(t_ph *philosoper)
{
	sem_wait(philosoper->manager->forks);
	if (philosoper->is_end)
	{
		sem_post(philosoper->manager->forks);
		return (0);
	}
	message(philosoper, FORK);
	sem_wait(philosoper->manager->forks);
	if (philosoper->is_end)
	{
		sem_post(philosoper->manager->forks);
		sem_post(philosoper->manager->forks);
		return (0);
	}
	message(philosoper, FORK);
	return (1);
}

int	put_fork(t_ph *philosoper)
{
	sem_post(philosoper->manager->forks);
	sem_post(philosoper->manager->forks);
	if (philosoper->is_end)
		return (0);
	message(philosoper, SLEEP);
	usleep(philosoper->manager->sleep_time * 1000);
	if (philosoper->is_end)
		return (0);
	message(philosoper, THINK);
	return (1);
}
