/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:35:38 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 18:25:50 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static t_ph		*init_ph(int i)
{
	t_ph	*ph;

	ph = NULL;
	if (!(ph = malloc(sizeof(t_ph))))
		return (NULL);
	ph->id = i;
	ph->info = NULL;
	ph->num_of_eat = 0;
	if (!(ph->last_meal_time = malloc(sizeof(struct timeval))))
	{
		free(ph);
		return (NULL);
	}
	return (ph);
}

int				set_philosophers(t_manager *manager)
{
	t_ph	**phs;
	int		i;

	if (!(phs = malloc(sizeof(t_ph *) * (manager->info->num_of_ph + 1))))
		return (ERROR);
	i = -1;
	while (++i < manager->info->num_of_ph)
	{
		if (!(phs[i] = init_ph(i)))
			return (ERROR);
	}
	phs[i] = NULL;
	manager->phs = phs;
	return (SUCCESS);
}
