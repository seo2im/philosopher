/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:07:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 18:54:02 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	destory(t_ph *ph)
{
	;	
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
	}
	free(phs);
}

int		init_manager(t_manager *manager)
{
	manager->info = NULL;
	manager->phs = NULL;
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
	init_semaphore(&manager);
	if (!process(&manager))
		ft_error("PROCESS ERROR : something wrong in process", 1);
	
	clear_manager(&manager);
}
