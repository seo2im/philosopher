/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:24:38 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 21:34:50 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		eating(t_ph *ph)
{
	if (!ph->last_meal_time)
		return (1);
	gettimeofday(ph->last_meal_time, NULL);
	message(ph, "eating", ph->last_meal_time);
	ph->num_of_eat++;
	usleep(ph->info->eat_time * 1000); //TODO : get time of usleep during eating time;
	return (0);
}

int		eat_check(t_ph *ph)
{
	struct timeval	current;
	int				ret;
	
	gettimeofday(&current, NULL);
	if (!ph->last_meal_time ||
		ft_time(&current) - ft_time(ph->last_meal_time) > ph->info->dead_time)
	{
		free(ph->last_meal_time);
		message(ph, "died", &current);
		ph->last_meal_time = NULL;
		ret = -1;
	}
	else
		ret = eating(ph);
	sem_post(ph->forks);
	sem_post(ph->forks);
	sem_post(ph->eat_available);
	return (ret);
}

int		eat(t_ph *ph)
{
	struct timeval	current;

	if (eat_check(ph))
		return (-1);
	if (ph->num_of_eat == ph->info->eat_must)
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "sleeping", &current);
	usleep(ph->info->sleep_time * 1000); //TODO : ft_usleep diff check;
	if (!ph->last_meal_time)
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "thinking", &current);
	return (0);
}

int		take_fork(t_ph *ph)
{
	struct timeval	current;

	if (!ph->last_meal_time)
		return (1);
	if (sem_wait(ph->eat_available))
		return (1);
	if (sem_wait(ph->forks))
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "take fork", &current);
	if (sem_wait(ph->forks))
		return (1);
	gettimeofday(&current, NULL);
	message(ph, "take fork", &current);
	if (sem_post(ph->eat_available))
		return (1);
	return (0);
}

void	*routine(t_ph *ph)
{
	int		ret;

	while (!take_fork(ph) && !(ret = eat(ph)))
		;
	if (ret == -1)
		exit(1);
	exit(0);
}

#include <stdio.h>

int		wait_process(t_manager *manager)
{
	int		num;
	int		state;
	t_ph	**phs;

	phs = manager->phs;
	state = 0;
	num = 0;
	while (!state && num < manager->info->num_of_ph)
	{
		waitpid(-1, &state, 0);
		num++;	
	}
	if (state)
	{
		phs = manager->phs;
		while (*phs)
		{
			kill((*phs)->pid, SIGINT);
			phs++;
		}
	}
	return (0);
}

int		process(t_manager *manager)
{
	t_ph	**phs;
	int		pid;
	int		i;

	if (gettimeofday(manager->info->start_time, NULL))
		return (ERROR);
	phs = manager->phs;
	i = -1;
	while (phs[++i])
	{
		if (!(phs[i]->info = copy_info(manager->info)))
			return (ERROR);	
		phs[i]->last_meal_time->tv_sec = phs[i]->info->start_time->tv_sec;
		phs[i]->last_meal_time->tv_usec = phs[i]->info->start_time->tv_usec;
		phs[i]->num_of_eat = 0;
		if (!(pid = fork()))
			routine(phs[i]);
		phs[i]->pid = pid;
	}
	return (wait_process(manager) ? ERROR : SUCCESS);
}
