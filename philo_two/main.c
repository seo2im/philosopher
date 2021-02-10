/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:54:20 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 14:17:33 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	clear(t_manager *manager)
{
	char	*name;
	int		i;

	sem_unlink("fork_sem");
	sem_unlink("msg_sem");
	sem_unlink("dead_sem");
	i = -1;
	while (++i < manager->info->num_of_ph)
	{
		name = sem_name("ph_sem", i);
		sem_unlink(name);
		free(name);
		name = sem_name("eat_sem", i);
		sem_unlink(name);
		free(name);
	}
	free(manager->info);
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
