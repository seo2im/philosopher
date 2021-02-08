/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:26:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 20:34:51 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	setup_info(t_manager *manager, char *argv[], int argc)
{
	t_info	*info;

	if (!(info = malloc(sizeof(t_info))))
		return (ERROR);
	info->num_of_ph = ft_atoi(argv[1]);
	info->time_dead = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->num_eat = ft_atoi(argv[5]);
	else
		info->num_eat = 0;
	manager->info = info;
	return (SUCCESS);
}

static int	setup_ph(t_manager *manager)
{
	t_ph	**phs;
	int		i;

	if (!(phs = malloc(sizeof(t_ph *) * (manager->info->num_of_ph + 1))))
		return (ERROR);
	i = -1;
	while (++i < manager->info->num_of_ph)
	{
		phs[i] = NULL;
		if (!(phs[i] = malloc(sizeof(t_ph))))
			return (ERROR);
		phs[i]->id = i;
		phs[i]->is_eat = FALSE;
		phs[i]->left_fork = i;
		phs[i]->right_fork = (i + 1) % manager->info->num_of_ph;
		phs[i]->info = manager->info;
		pthread_mutex_init(&phs[i]->ph_mutex, NULL);
		pthread_mutex_init(&phs[i]->eat_mutex, NULL);
		pthread_mutex_lock(&phs[i]->eat_mutex);
		
	}
	phs[i] = NULL;
	manager->phs = phs;
	return (SUCCESS);
}

static int	setup_mutex(t_manager *manager)
{
	int	i;

	pthread_mutex_init(&manager->msg_mutex, NULL);
	pthread_mutex_init(&manager->dead_mutex, NULL);
	pthread_mutex_lock(&manager->dead_mutex);
	if (!(manager->fork_mutex
		= malloc(sizeof(pthread_mutex_t) * manager->info->num_of_ph)))
		return (ERROR);
	i = -1;
	while (++i < manager->info->num_of_ph)
		pthread_mutex_init(&manager->fork_mutex[i], NULL);
	i = -1;
	while (manager->phs[++i])
	{
		manager->phs[i]->fork_mutex = manager->fork_mutex;
		manager->phs[i]->msg_mutex = manager->msg_mutex;
		manager->phs[i]->dead_mutex = manager->dead_mutex;
	}
	return (SUCCESS);
}


int			setup_manager(t_manager *manager, char *argv[], int argc)
{
	manager->info = NULL;
	manager->phs = NULL;
	manager->fork_mutex = NULL;
	if (!setup_info(manager, argv, argc))
		return (ERROR);
	if (!setup_ph(manager))
		return (ERROR);
	if (!setup_mutex(manager))
		return (ERROR);
	return (SUCCESS);
}
