/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:19:11 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 16:23:40 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	ph->thread = NULL;
	ph->num_of_eat = 0;
	if (!(ph->last_meal_time = malloc(sizeof(struct timeval))))
	{
		free(ph);
		return (NULL);
	}
	if (!(ph->thread = malloc(sizeof(pthread_t))))
	{
		free(ph->last_meal_time);
		free(ph);
		return (NULL);
	}
	if (!(ph->last_meal_mutex = malloc(sizeof(pthread_mutex_t))))
	{
		free(ph->last_meal_time);
		free(ph->thread);
		free(ph);
		return (NULL);
	}
	ph->message = manager->message;
	ph->info = NULL;
	return (ph);
}

static t_fork	*init_fork()
{
	t_fork	*fork;

	if (!(fork = malloc(sizeof(t_fork))))
		return (NULL);
	if (!(fork->mutex = malloc(sizeof(pthread_mutex_t))))
	{
		free(fork);
		return (NULL);
	}
	if (pthread_mutex_init(fork->mutex, NULL))
	{
		free(fork->mutex);
		free(fork);
		return (NULL);
	}
	return (fork);
}

void			set_fork(t_ph **phs)
{
	t_fork	*fork;
	int		i;

	fork = init_fork();
	fork->nb_last = 0;
	i = -1;
	while (phs[++i])
	{
		phs[i]->left_fork = fork;
		if (phs[i + 1] != NULL)
		{
			fork = init_fork();
			phs[i]->right_fork = fork;
		}
		else
			phs[i]->right_fork = phs[0]->left_fork;
	}
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
	set_fork(phs);
	manager->phs = phs;
	return (SUCCESS);	
}
