/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:52:51 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 15:36:24 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include "base.h"

typedef struct		s_info
{
	int				num_of_ph;
	int				dead_time;
	int				eat_time;
	int				sleep_time;
	int				eat_must;
	struct timeval	*start_time;
}					t_info;

typedef struct		s_fork
{
	pthread_mutex_t	*mutex;
	int				nb_last;
}					t_fork;

typedef struct		s_ph
{
	int				id;
	t_info			*info;
	pthread_t		*thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*last_meal_mutex;
	struct timeval	*last_meal_time;
	pthread_mutex_t	*message;
	int				num_of_eat;
	int				is_died;
}					t_ph;

typedef struct		s_manager
{
	t_info			*info;
	t_ph			**phs;
	pthread_mutex_t	*message;
}					t_manager;

#endif
