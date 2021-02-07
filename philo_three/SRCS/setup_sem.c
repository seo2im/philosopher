/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_sem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:34:12 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:39:14 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int				init_semaphore(t_manager *manager)
{
	int		i;

	sem_unlink("message");
	if ((manager->message = sem_open("message",
		O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
		return (ERROR);
	sem_unlink("forks");
	if ((manager->forks = sem_open("forks",
		O_CREAT | O_TRUNC | O_RDWR, S_IRWXU,
		manager->info->num_of_ph)) == SEM_FAILED)
		return (ERROR);
	sem_unlink("eat_available");
	if ((manager->eat_available = sem_open("eat_available",
		O_CREAT | O_TRUNC | O_RDWR, S_IRWXU,
		manager->info->num_of_ph / 2)) == SEM_FAILED)
		return (ERROR);
	i = -1;
	while (manager->phs[++i])
	{
		manager->phs[i]->eat_available = manager->eat_available;
		manager->phs[i]->message = manager->message;
		manager->phs[i]->forks = manager->forks;
	}
	return (SUCCESS);
}
