/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:29:09 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 16:27:59 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		*ph_free(t_ph *ph)
{
	if (ph->thread)
		free(ph->thread);
	if (ph->last_meal_time)
		free(ph->thread);
	free(ph);
	return (NULL);
}

static t_ph		*init_ph(t_manager *manager, int i)
{
	t_ph	*ph;

	ph = NULL;
	if (!(ph = malloc(sizeof(t_ph))))
		return (NULL);
	ph->id = i;
	ph->info = NULL;
	ph->thread = NULL;
	ph->num_of_eat = 0;
	ph->last_meal_time = NULL;
	if (!(ph->last_meal_time = malloc(sizeof(struct timeval))))
		return (ph_free(ph));
	if (!(ph->thread = malloc(sizeof(pthread_t))))
		return (ph_free(ph));
	if (!(ph->last_meal_mutex = malloc(sizeof(pthread_mutex_t))))
		return (ph_free(ph));
	ph->message = manager->message;
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
		if (!(phs[i] = init_ph(manager, i)))
			return (ERROR);
	}
	phs[i] = NULL;
	set_fork(phs);
	manager->phs = phs;
	return (SUCCESS);
}
