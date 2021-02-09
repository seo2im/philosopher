/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:54:20 by seolim            #+#    #+#             */
/*   Updated: 2021/02/09 14:07:55 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	clear(t_manager *manager)
{
	int	num_of_ph;
	int	i;

	num_of_ph = manager->info->num_eat;
	sem_close(&manager->info->fork_sem);
	sem_close(&manager->info->msg_sem);
	sem_close(&manager->info->dead_sem);
	free(manager->info);
	i = -1;
	while (++i < num_of_ph)
	{
		sem_close(manager->phs[i]->ph_sem);
		sem_close(manager->phs[i]->eat_sem);
		free(manager->phs[i]);
	}
	free(manager->phs);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_manager manager;

	if (argc < 5 || argc > 6)
		return (ERROR + 1);
	if (!setup_manager(&manager, argv, argc))
		return (ERROR + 1);
	process(&manager);
	sem_wait(manager.info->dead_sem);
	return (clear(&manager));
}
