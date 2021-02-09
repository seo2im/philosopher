/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:54:20 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 00:04:50 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	clear(t_manager *manager)
{
	free(manager->info->fork_mutex);
	free(manager->phs);
	free(manager->info);
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
