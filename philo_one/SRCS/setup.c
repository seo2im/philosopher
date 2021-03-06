/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:26:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/09 19:51:09 by seolim           ###   ########.fr       */
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
	int		i;

	if (!(manager->phs =
		malloc(sizeof(*(manager->phs)) * manager->info->num_of_ph)))
		return (ERROR);
	i = -1;
	while (++i < manager->info->num_of_ph)
	{
		manager->phs[i].id = i;
		manager->phs[i].is_eat = FALSE;
		manager->phs[i].left_fork = i;
		manager->phs[i].right_fork = (i + 1) % manager->info->num_of_ph;
		manager->phs[i].num_eat = 0;
		manager->phs[i].info = manager->info;
		pthread_mutex_init(&manager->phs[i].ph_mutex, NULL);
		pthread_mutex_init(&manager->phs[i].eat_mutex, NULL);
		pthread_mutex_lock(&manager->phs[i].eat_mutex);
	}
	return (SUCCESS);
}

static int	setup_mutex(t_manager *manager)
{
	int	i;

	pthread_mutex_init(&manager->info->msg_mutex, NULL);
	pthread_mutex_init(&manager->info->dead_mutex, NULL);
	pthread_mutex_lock(&manager->info->dead_mutex);
	if (!(manager->info->fork_mutex =
		malloc(sizeof(pthread_mutex_t) * manager->info->num_of_ph)))
		return (ERROR);
	i = -1;
	while (++i < manager->info->num_of_ph)
		pthread_mutex_init(&manager->info->fork_mutex[i], NULL);
	return (SUCCESS);
}

int			setup_manager(t_manager *manager, char *argv[], int argc)
{
	manager->info = NULL;
	manager->phs = NULL;
	if (!setup_info(manager, argv, argc))
		return (ERROR);
	if (!setup_ph(manager))
		return (ERROR);
	if (!setup_mutex(manager))
		return (ERROR);
	return (SUCCESS);
}
