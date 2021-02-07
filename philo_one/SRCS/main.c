/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:07:31 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 16:52:58 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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

	system("leaks philo_one > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
}
