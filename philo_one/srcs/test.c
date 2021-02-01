/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:34:46 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:34:47 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	print_info(t_manager *manager)
{
	printf("ph_num : %d\n", manager->ph_num);
	printf("eat : %d\n", manager->must_eat_num);
	int i = -1;
	while (++i < manager->ph_num)
	{
		printf("ph id : %d\n", manager->ph_list[i].id);
		printf("ph lfork : %d\n", manager->ph_list[i].left_fork);
		printf("ph rfork : %d\n", manager->ph_list[i].right_fork);
		
	}
}
