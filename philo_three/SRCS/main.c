/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:07:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 18:18:38 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		main(int argc, char *argv[])
{
	t_manager	manager;

	if (argc != 5 && argc != 6)
		return (ft_error("ARGV ERROR : Not compelete argv", 1));
	if (!init_manager(&manager))
		return (ft_error("MALLOC ERROR : timeval malloc error", 1));
	set_info(&manager, argc, argv);
	set_philosophers(&manager);
	init_semaphore(&manager);
	if (!process(&manager))
		ft_error("PROCESS ERROR : something wrong in process", 1);
	clear_manager(&manager);
}
