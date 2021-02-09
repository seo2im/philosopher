/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:54:20 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 00:30:50 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int	clear(t_manager *manager)
{
	free(manager->info);
	free(manager->phs);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_manager	manager;
	int			i;

	if (argc < 5 || argc > 6)
		return (ERROR + 1);
	if (!setup_manager(&manager, argv, argc))
		return (ERROR + 1);
	process(&manager);
	sem_wait(manager.info->dead_sem);
	i = -1;
	while (++i < manager.info->num_of_ph)
		kill(manager.phs[i].pid, SIGKILL);
	return (clear(&manager));
}
