/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:18:14 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 19:13:36 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
		if (phs[i]->thread)
			free(phs[i]->thread);
		free(phs[i]);
	}
	free(phs);
}

void	sem_free(t_manager *manager)
{
	int	i;

	if (manager->message)
		sem_close(manager->message);
	if (manager->forks)
		sem_close(manager->forks);
	if (manager->eat_available)
		sem_close(manager->eat_available);
	i = -1;
	while (manager->phs[++i])
		if (manager->phs[i]->last_meal_sem)
			sem_close(manager->phs[i]->last_meal_sem);
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
