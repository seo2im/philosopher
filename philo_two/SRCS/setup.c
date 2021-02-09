/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:26:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/09 14:02:34 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	info->dead_sem = NULL;
	info->fork_sem = NULL;
	info->msg_sem = NULL;
	info->cur_eat_count = 0;
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
		phs[i]->num_eat = 0;
		phs[i]->info = manager->info;
		sem_unlink("ph_sem");
		phs[i]->ph_sem = sem_open("ph_sem", O_CREAT | O_EXCL, 0644, 1);
		sem_unlink("eat_sem");
		phs[i]->eat_sem = sem_open("eat_sem", O_CREAT | O_EXCL, 0644, 0);
	}
	phs[i] = NULL;
	manager->phs = phs;
	return (SUCCESS);
}

static int	setup_semaphore(t_manager *manager)
{
	sem_unlink("fork_sem");
	manager->info->fork_sem = sem_open("fork_sem", O_CREAT | O_EXCL, 0644,
					manager->info->num_of_ph);
	sem_unlink("msg_sem");
	manager->info->msg_sem = sem_open("msg_sem", O_CREAT | O_EXCL, 0644, 1);
	sem_unlink("dead_sem");
	manager->info->dead_sem = sem_open("dead_sem", O_CREAT | O_EXCL, 0644, 0);
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
	if (!setup_semaphore(manager))
		return (ERROR);
	return (SUCCESS);
}
