/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 14:20:06 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 17:44:11 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	message(t_ph *ph, char *str, struct timeval *current)
{
	char	*id_str;
	char	*time_str;

	id_str = ft_itoa(ph->id);
	time_str = ft_itoa(ft_time(current) - ft_time(ph->info->start_time));
	sem_wait(ph->message);
	ft_write(time_str);
	ft_write("ms phiosopher ");
	ft_write(id_str);
	ft_write(" is ");
	ft_write_n(str);
	free(id_str);
	free(time_str);
	sem_post(ph->message);
}
