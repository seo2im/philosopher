/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:23:16 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 18:12:40 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	sem_unlink("last_meal");
	if ((ph->last_meal_sem = sem_open("last_meal",
		O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
		return (ph_free(ph));
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
	manager->phs = phs;
	return (SUCCESS);
}
