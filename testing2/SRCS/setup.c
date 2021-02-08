/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:26:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 22:57:31 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	setup_ph(t_manager *manager)
{
	int		i;

	i = -1;
	while (++i < manager->num_of_ph)
	{
		manager->phs[i].id = i;
		manager->phs[i].is_eat = FALSE;
		manager->phs[i].left_fork = i;
		manager->phs[i].right_fork = (i + 1) % manager->num_of_ph;
		manager->phs[i].num_eat = 0;
		manager->phs[i].manager = manager;
		pthread_mutex_init(&manager->phs[i].ph_mutex, NULL);
		pthread_mutex_init(&manager->phs[i].eat_mutex, NULL);
		pthread_mutex_lock(&manager->phs[i].eat_mutex);
	}
	return (SUCCESS);
}

static int	setup_mutex(t_manager *manager)
{
	int	i;

	pthread_mutex_init(&manager->msg_mutex, NULL);
	pthread_mutex_init(&manager->dead_mutex, NULL);
	pthread_mutex_lock(&manager->dead_mutex);
	if (!(manager->fork_mutex
		= malloc(sizeof(*(manager->fork_mutex)) * manager->num_of_ph)))
		return (ERROR);
	i = -1;
	while (++i < manager->num_of_ph)
		pthread_mutex_init(&manager->fork_mutex[i], NULL);
	return (SUCCESS);
}


int			setup_manager(t_manager *manager, char *argv[], int argc)
{
	manager->num_of_ph = ft_atoi(argv[1]);
	manager->time_dead = ft_atoi(argv[2]);
	manager->time_eat = ft_atoi(argv[3]);
	manager->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		manager->num_eat = ft_atoi(argv[5]);
	else
		manager->num_eat = 0;
	manager->fork_mutex = NULL;
	manager->phs = NULL;
	if (!(manager->phs = malloc(sizeof(*(manager->phs)) * manager->num_of_ph)))
		return (ERROR);
	if (!setup_ph(manager))
		return (ERROR);
	if (!setup_mutex(manager))
		return (ERROR);
	return (SUCCESS);
}
