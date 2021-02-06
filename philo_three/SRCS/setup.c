/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:19:11 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 20:04:48 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void			change_order(t_manager *manager)
{
	int		i;
	int		j;
	t_ph	**phs;
	t_ph	*temp[manager->info->num_of_ph];

	phs = manager->phs;
	i = -1;
	while (phs[++i])
		if (i % 2 == 0)
		{
			temp[i / 2] = phs[i];
			j = i / 2;
		}
	i = -1;
	while (phs[++i])
		if (i % 2 == 1)
			temp[++j] = phs[i];
	i = -1;
	while (phs[++i])
		phs[i] = temp[i];
	phs[i] = NULL;
}

/*
*	if error find (ex> string input...), not care it
*/
int				set_info(t_manager *manager, int argc, char *argv[])
{
	t_info	*info;

	if (!(info = malloc(sizeof(t_info))))
		return (ERROR);
	info->num_of_ph = ft_atoi(argv[1]);
	info->dead_time = ft_atoi(argv[2]);
	info->eat_time = ft_atoi(argv[3]);
	info->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		info->eat_must = ft_atoi(argv[5]);
	else 
		info->eat_must = -1;
	if (!(info->start_time = malloc(sizeof(struct timeval))))
	{
		free(info);
		return (ERROR);
	}
	manager->info = info;
	manager->message = NULL;
	manager->forks = NULL;
	manager->eat_available = NULL;
	return (SUCCESS);
}

int				init_semaphore(t_manager *manager)
{
	int		i;

	sem_unlink("message");
	if ((manager->message = sem_open("message", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, 1)) == SEM_FAILED)
		return (ERROR);
	sem_unlink("forks");
	if ((manager->forks = sem_open("forks", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, manager->info->num_of_ph)) == SEM_FAILED)
		return (ERROR);
	sem_unlink("eat_available");
	if ((manager->eat_available = sem_open("eat_available", O_CREAT | O_TRUNC | O_RDWR, S_IRWXU, manager->info->num_of_ph / 2)) == SEM_FAILED)
		return (ERROR);
	i = -1;
	while (manager->phs[++i])
	{
		manager->phs[i]->eat_available = manager->eat_available;
		manager->phs[i]->message = manager->message;
		manager->phs[i]->forks = manager->forks;
	}
	return (SUCCESS);
}

t_info			*copy_info(t_info *src)
{
	t_info	*dest;

	if (!(dest = malloc(sizeof(t_info))))
		return (NULL);
	dest->num_of_ph = src->num_of_ph;
	dest->dead_time = src->dead_time;
	dest->eat_time = src->eat_time;
	dest->sleep_time = src->sleep_time;
	dest->eat_must = src->eat_must;
	if (!(dest->start_time = malloc(sizeof(struct timeval))))
	{
		free(dest);
		return (NULL);
	}
	dest->start_time->tv_sec = src->start_time->tv_sec;
	dest->start_time->tv_usec = src->start_time->tv_usec;
	return (dest);
}

static t_ph		*init_ph(t_manager *manager, int i)
{
	t_ph	*ph;

	ph = NULL;
	if (!(ph = malloc(sizeof(t_ph))))
		return (NULL);
	ph->id = i;
	ph->info = NULL;
	ph->num_of_eat = 0;
	if (!(ph->last_meal_time = malloc(sizeof(struct timeval))))
	{
		free(ph);
		return (NULL);
	}
	ph->info = NULL;
	return (ph);
}

int				set_philosophers(t_manager *manager)
{
	t_ph	**phs;
	int		i;
	
	if (!(phs = malloc(sizeof(t_ph *) *(manager->info->num_of_ph + 1))))
		return (ERROR);
	i = -1;
	while (++i < manager->info->num_of_ph)
	{
		if(!(phs[i] = init_ph(manager, i)))
			return (ERROR);
	}
	phs[i] = NULL;
	manager->phs = phs;
	return (SUCCESS);
}
