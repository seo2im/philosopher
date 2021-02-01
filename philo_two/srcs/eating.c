/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:46:40 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 17:18:35 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

void	eating(t_ph *philosoper)
{
	sem_wait(philosoper->live);
	philosoper->dead_limit = ft_gettime()
			+ philosoper->manager->dead_time * 1000;
	message(philosoper, EAT);
	usleep(philosoper->manager->eat_time * 1000);
	philosoper->eat_count++;
	sem_post(philosoper->live);
}
