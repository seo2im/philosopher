/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:54:49 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 00:51:46 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	message(t_ph *ph, char *str, int is_die, int is_over)
{
	static int	done = 0;
	char		*time_str;
	char		*id_str;

	sem_wait(ph->info->msg_sem);
	if (!done)
	{
		time_str = ft_itoa(ft_gettime() - ph->info->start_time);
		id_str = ft_itoa(ph->id);
		ft_write(1, time_str);
		ft_write(1, "ms\t");
		if (!is_over)
			ft_write(1, id_str);
		ft_write(1, " ");
		ft_write_n(1, str);
		if (is_die)
			done = 1;
		free(id_str);
		free(time_str);
	}
	sem_post(ph->info->msg_sem);
}
