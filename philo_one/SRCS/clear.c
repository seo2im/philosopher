/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:23:43 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 16:50:04 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_ph_free(t_ph **phs)
{
	int	i;

	i = -1;
	while (phs[++i])
	{
		if (phs[i]->info)
		{
			free(phs[i]->info->start_time);
			free(phs[i]->info);
		}
		if (phs[i]->last_meal_time)
			free(phs[i]->last_meal_time);
		if (phs[i]->thread)
			free(phs[i]->thread);
		if (phs[i]->last_meal_mutex)
		{
			pthread_mutex_destroy(phs[i]->last_meal_mutex);
			free(phs[i]->last_meal_mutex);
		}
		
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

void	clear_manager(t_manager *manager)
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
