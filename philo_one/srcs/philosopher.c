/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:34:18 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 17:41:56 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

static int	init_philosoper_list(t_manager *manager)
{
	t_ph	*list;
	int		i;

	if (!(list = malloc(sizeof(t_ph) * (manager->ph_num + 1))))
		return (ft_error("Init_philosoper : malloc error", ERROR));
	i = -1;
	while (++i < manager->ph_num)
	{
		list[i].id = i;
		list[i].left_fork = i;
		list[i].right_fork = (i + 1) % manager->ph_num;
		list[i].eat_count = 0;
		list[i].manager = manager;
		list[i].is_end = FALSE;
		pthread_mutex_init(&list[i].live, NULL);
	}
	manager->ph_list = list;
	return (SUCCESS);
}

static int	init_mutex(t_manager *manager)
{
	int	i;

	pthread_mutex_init(&manager->output, NULL);
	if (!(manager->forks = malloc(sizeof(pthread_mutex_t) * manager->ph_num)))
		return (ft_error("Init_mutex : malloc error", ERROR));
	i = -1;
	while (++i < manager->ph_num)
		pthread_mutex_init(&manager->forks[i], NULL);
	return (SUCCESS);
}

int			init_manager(t_manager *manager, char *argv[], int argc)
{
	if ((manager->ph_num = ft_atoi(argv[0])) < 0)
		return (ft_error("Init_manager : argv[0] under 0", ERROR));
	if ((manager->dead_time = ft_atoi(argv[1])) < 0)
		return (ft_error("Init manager : argv[1] under 0", ERROR));
	if ((manager->eat_time = ft_atoi(argv[2])) < 0)
		return (ft_error("Init manager : argv[2] under 0", ERROR));
	if ((manager->sleep_time = ft_atoi(argv[3])) < 0)
		return (ft_error("Init manager : argv[3] under 0", ERROR));
	if (argc == 6)
	{
		if ((manager->must_eat_num = ft_atoi(argv[4])) < 0)
			return (ft_error("Init_manager : argv[4] under 0", ERROR));
	}
	else
		manager->must_eat_num = 0;
	manager->end_count = 0;
	manager->forks = NULL;
	manager->ph_list = NULL;
	if (init_philosoper_list(manager) == ERROR)
		return (ft_error("Init_manager : philosoper init error", ERROR));
	if (init_mutex(manager) == ERROR)
		return (ft_error("Init_manager : mutex init error", ERROR));
	return (SUCCESS);
}

int			clear(t_manager *manager)
{
	int i;

	if (manager->forks)
	{
		i = -1;
		while (++i < manager->ph_num)
			pthread_mutex_destroy(&manager->forks[i]);
		free(manager->forks);
	}
	if (manager->ph_list)
	{
		i = -1;
		while (++i < manager->ph_num)
			pthread_mutex_destroy(&manager->ph_list[i].live);
		free(manager->ph_list);
	}
	pthread_mutex_destroy(&manager->output);
	return (SUCCESS);
}
