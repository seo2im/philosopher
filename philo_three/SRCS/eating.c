/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 19:02:12 by seolim            #+#    #+#             */
/*   Updated: 2021/02/09 14:46:02 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	take_fork(t_ph *ph)
{
	sem_wait(ph->info->fork_sem);
	message(ph, "take fork", FALSE);
	sem_wait(ph->info->fork_sem);
	message(ph, "take fork", FALSE);
}

void	putoff_fork(t_ph *ph)
{
	message(ph, "is sleep", FALSE);
	sem_post(ph->info->fork_sem);
	sem_post(ph->info->fork_sem);
	ft_usleep(ph->info->time_sleep * 1000);
}

void	eat(t_ph *ph)
{
	sem_wait(ph->ph_sem);
	ph->is_eat = TRUE;
	ph->time_last_meal = ft_gettime();
	ph->time_dead_limit = ph->time_last_meal + ph->info->time_dead;
	message(ph, "is eating", FALSE);
	ft_usleep(ph->info->time_eat * 1000);
	ph->num_eat++;
	ph->is_eat = FALSE;
	sem_post(ph->ph_sem);
	sem_post(ph->eat_sem);
}
