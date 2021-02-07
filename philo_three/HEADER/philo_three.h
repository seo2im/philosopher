/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:16:19 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 18:19:56 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include "utils.h"

int			set_info(t_manager *manager, int argc, char *argv[]);
int			set_philosophers(t_manager *manager);
t_info		*copy_info(t_info *src);
void		message(t_ph *ph, char *str, struct timeval *current);
void		change_order(t_manager *manager);
int			process(t_manager *manager);
int			init_semaphore(t_manager *manager);
int			init_manager(t_manager *manager);
void		clear_manager(t_manager *manager);
int			eat(t_ph *ph);
int			take_fork(t_ph *ph);

#endif
