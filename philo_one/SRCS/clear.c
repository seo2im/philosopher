/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:23:43 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 17:15:38 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void free_one(t_ph *ph)
{
	if (ph->info)
	{
		free(ph->info->start_time);
		free(ph->info);
	}
	if (ph->last_meal_time)
		free(ph->last_meal_time);
	if (ph->thread)
		free(ph->thread);
	if (ph->last_meal_mutex)
	{
		pthread_mutex_destroy(ph->last_meal_mutex);
		free(ph->last_meal_mutex);
	}
}

void		ft_ph_free(t_ph **phs)
{
	int	i;

	i = -1;
	while (phs[++i])
	{
		free_one(phs[i]);
		if (phs[i]->left_fork)
		{
			pthread_mutex_destroy(phs[i]->left_fork->mutex);
			free(phs[i]->left_fork->mutex);
			free(phs[i]->left_fork);
		}
		free(phs[i]);
	}
	free(phs);
}

void		clear_manager(t_manager *manager)
{
	if (manager->info)
	{
		free(manager->info->start_time);
		free(manager->info);
	}
	if (manager->phs)
		ft_ph_free(manager->phs);
	pthread_mutex_destroy(manager->message);
	free(manager->message);
}
