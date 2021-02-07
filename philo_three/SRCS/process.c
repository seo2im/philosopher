/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 16:24:38 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:38:47 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*routine(t_ph *ph)
{
	int		ret;

	while (!take_fork(ph) && !(ret = eat(ph)))
		;
	if (ret == -1)
		exit(1);
	exit(0);
}

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
