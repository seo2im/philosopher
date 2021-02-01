/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:33:01 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:37:06 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

int	eating(t_ph *philosoper)
{
	pthread_mutex_lock(&philosoper->live);
	message(philosoper, EAT);
	usleep(philosoper->manager->eat_time * 1000);
	philosoper->dead_limit = ft_gettime() + philosoper->manager->dead_time;
	philosoper->eat_count++;
	pthread_mutex_unlock(&philosoper->live);
	return (1);
}
