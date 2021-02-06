/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:16:19 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 18:19:42 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHIO_ONE_H
# define PHIO_ONE_H

# include "utils.h"

int			set_info(t_manager *manager, int argc, char *argv[]);
int			set_philosophers(t_manager *manager);
t_info		*copy_info(t_info *src);
void		message(t_ph *ph, char *str, struct timeval *current);
void		change_order(t_manager *manager);
int			process(t_manager *manager);
int			init_semaphore(t_manager *manager);

#endif
