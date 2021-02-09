/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:55:02 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 00:32:45 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include "base.h"
# include "utils.h"
# include "structure.h"

int		setup_manager(t_manager *manager, char *argv[], int argc);
int		process(t_manager *manager);
void	putoff_fork(t_ph *ph);
void	take_fork(t_ph *ph);
void	eat(t_ph *ph);
void	message(t_ph *ph, char *str, int is_die, int is_over);

#endif
