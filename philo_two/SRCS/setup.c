/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:19:11 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:24:44 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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

int				init_manager(t_manager *manager)
{
	manager->info = NULL;
	manager->phs = NULL;
	return (SUCCESS);
}
