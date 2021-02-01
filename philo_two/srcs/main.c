/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:47:23 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:47:38 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*dead_check(void *arg)
{
	t_ph	*philosoper;

	philosoper = (t_ph *)arg;
	while (TRUE)
	{
		sem_wait(philosoper->live);
		if (ft_gettime() >= philosoper->dead_limit)
		{
			message(philosoper, DEAD);
			philosoper->is_end = TRUE;
			if (philosoper->manager->end_count != philosoper->manager->ph_num)
				philosoper->manager->end_count++;
			sem_post(philosoper->live);
			return ((void *)0);
		}
		sem_post(philosoper->live);
	}
}

static void *eat_check(void *arg)
{
	t_ph	*philosoper;

	philosoper = (t_ph *)arg;
	while (TRUE)
	{
		sem_wait(philosoper->live);
		if (philosoper->eat_count >= philosoper->manager->must_eat_num)
		{
			message(philosoper, END);
			philosoper->is_end = TRUE;
			philosoper->manager->end_count++;
			return ((void *)0);
		}
		sem_post(philosoper->live);
	}
}

static void *routine(void *arg)
{
	t_ph		*philosoper;
	pthread_t	pid;

	philosoper = (t_ph *)arg;
	if (pthread_create(&pid, NULL, &dead_check, arg) != 0)
		return ((void *)1);
	pthread_detach(pid);
	if (philosoper->manager->must_eat_num > 0)
	{
		if (pthread_create(&pid, NULL, &eat_check, arg) != 0)
			return ((void*)1);
		pthread_detach(pid);
	}
	while (!philosoper->is_end)
	{
		if (!get_fork(philosoper))
			return ((void *)0);
		eating(philosoper);
		if (!put_fork(philosoper))
			return ((void *)0);
	}
	return ((void *)0);
}

static int	process(t_manager *manager)
{
	pthread_t	pid;
	int			i;

	manager->start_time = ft_gettime();
	i = -1;
	while (++i < manager->ph_num)
	{
		manager->ph_list[i].dead_limit = ft_gettime() + manager->dead_time;
		if (pthread_create(&pid, NULL, &routine, (void *)&manager->ph_list[i]))
			return (ft_error("Process : pid error", ERROR));
		pthread_detach(pid);
	}
	return (SUCCESS);
}

int main(int argc, char *argv[])
{
	t_manager manager;

	if (argc != 5 && argc != 6)
		return (ft_error("Main Error : argc not correct", 1));
	if ((init_manager(&manager, ++argv, argc)) == ERROR)
		return (ft_error("Main Error : init manager error", 1));
	if ((process(&manager) == ERROR))
		return (ft_error("Main Error : process error", 1));
	while (manager.end_count != manager.ph_num)
		;
	clear(&manager);
}
