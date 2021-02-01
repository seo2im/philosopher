/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:34:07 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:34:15 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosoper.h"

static int	print_state(t_ph *philosoper, int time)
{
	char	*time_msg;
	char	*id;
	
	if (!(time_msg = ft_itoa(time)))
		return (ft_error("Print_time : malloc error", ERROR));
	ft_write(time_msg);
	ft_write(" : ");
	free(time_msg);
	if (!(id = ft_itoa(philosoper->id)))
		return (ft_error("Print_time : malloc error", ERROR));
	ft_write("Philosoper ");
	ft_write(id);
	free(id);
	return (SUCCESS);
}

int			message(t_ph *philosoper, int kind)
{
	pthread_mutex_lock(&philosoper->manager->output);
	if ((print_state(philosoper, 
			ft_gettime() - philosoper->manager->start_time)) == ERROR)
		return (ft_error("Print_time : malloc error", ERROR));
	if (kind == EAT)
		ft_writen(" is eating");
	else if (kind == FORK)
		ft_writen(" take forks");
	else if (kind == THINK)
		ft_writen(" is thinking");
	else if (kind == SLEEP)
		ft_writen(" is sleeping");
	else if (kind == DEAD)
		ft_writen(" is Dead");
	else if (kind == END)
		ft_writen(" is Finished");
	pthread_mutex_unlock(&philosoper->manager->output);
	return (SUCCESS);
}
