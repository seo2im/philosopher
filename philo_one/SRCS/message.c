/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 18:54:49 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 19:46:22 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	message(t_ph *ph, char *str)
{
	static int	done = 0;
	char		*time_str;
	char		*id_str;

	pthread_mutex_lock(&ph->msg_mutex);
	if (!done)
	{
		ft_write_n(1, str);
		done = 1;
	}
}
