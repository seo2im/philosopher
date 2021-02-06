/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:07:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 17:09:53 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	destory(t_ph *ph)
{
	pthread_mutex_destroy(ph->left_fork->mutex);
	pthread_mutex_destroy(ph->last_meal_mutex);
}

void	ft_ph_free(t_ph **phs)
{
	int	i;

	i = -1;
	while (phs[++i])
	{
		if (phs[i]->info)
			free(phs[i]->info);
		if (phs[i]->thread)
			free(phs[i]->thread);
		free(phs[i]);
		if (phs[i]->left_fork)
		{
			free(phs[i]->left_fork->mutex);
			free(phs[i]->left_fork);
		}
	}
	free(phs);
}

int		init_manager(t_manager *manager)
{
	manager->info = NULL;
	manager->phs = NULL;
	if (!(manager->message = malloc(sizeof(pthread_mutex_t))))
		return (ERROR);
	if (pthread_mutex_init(manager->message, NULL))
	{
		free(manager->message);
		return (ERROR);
	}
	return (SUCCESS);
}

void	clear_manager(t_manager *manager)
{
	if (manager->info)
		free(manager->info);
	if (manager->phs)
		ft_ph_free(manager->phs);
}

int		main(int argc, char *argv[])
{
	t_manager	manager;

if (argc != 5 && argc != 6)
		return (ft_error("ARGV ERROR : Not compelete argv", 1));
	if (!init_manager(&manager))
		return (ft_error("MALLOC ERROR : timeval malloc error", 1));
	set_info(&manager, argc, argv);
	set_philosophers(&manager);
	change_order(&manager);

	if (!process(&manager))
		ft_error("PROCESS ERROR : something wrong in process", 1);

	clear_manager(&manager);
}
