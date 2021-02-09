/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:54:20 by seolim            #+#    #+#             */
/*   Updated: 2021/02/09 19:28:40 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	clear(t_manager *manager)
{
	int	num_of_ph;
	int	i;

	num_of_ph = manager->info->num_eat;
	i = -1;
	while (++i < num_of_ph)
		pthread_mutex_destroy(&manager->info->fork_mutex[i]);
	free(manager->info->fork_mutex);
	pthread_mutex_destroy(&manager->info->msg_mutex);
	pthread_mutex_destroy(&manager->info->dead_mutex);
	free(manager->info);
	i = -1;
	while (++i < num_of_ph)
	{
		pthread_mutex_destroy(&manager->phs[i].ph_mutex);
		pthread_mutex_destroy(&manager->phs[i].eat_mutex);
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
	pthread_mutex_lock(&manager.info->dead_mutex);
	pthread_mutex_unlock(&manager.info->dead_mutex);
	return (clear(&manager));
}
