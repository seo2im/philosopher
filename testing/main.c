/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:54:20 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 22:12:08 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	main(int argc, char *argv[])
{
	t_manager manager;

	if (argc < 5 || argc > 6)
		return (ERROR); // TODO : error return
	if (!setup_manager(&manager, argv, argc))
		return (ERROR); // TODO : error return
	process(&manager);
	pthread_mutex_lock(&manager.info->dead_mutex);
	pthread_mutex_unlock(&manager.info->dead_mutex);
}
