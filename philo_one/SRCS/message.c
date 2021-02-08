/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:54:49 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 21:30:33 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	message(t_ph *ph, char *str, int is_die)
{
	static int	done = 0;
	char		*time_str;
	char		*id_str;

	pthread_mutex_lock(&ph->msg_mutex);
	if (!done)
	{
		time_str = ft_itoa(ft_gettime() - ph->info->start_time);
		id_str = ft_itoa(ph->id);
		ft_write(1, time_str);
		ft_write(1, "ms\t");
		ft_write(1, id_str);
		ft_write(1, " ");
		ft_write_n(1, str);
		if (is_die)
			done = 1;
		free(id_str);
		free(time_str);
	}
	pthread_mutex_unlock(&ph->msg_mutex);
}
