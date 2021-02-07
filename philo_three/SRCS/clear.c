/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:37:23 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 18:05:13 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
		free(phs[i]);
	}
	free(phs);
}

void	sem_free(t_manager *manager)
{
	if (manager->message)
		sem_unlink("message");
	if (manager->forks)
		sem_unlink("forks");
	if (manager->eat_available)
		sem_unlink("eat_available");
}

void	clear_manager(t_manager *manager)
{
	if (manager->info)
	{
		free(manager->info->start_time);
		free(manager->info);
	}
	sem_free(manager);
	if (manager->phs)
		ft_ph_free(manager->phs);
}
