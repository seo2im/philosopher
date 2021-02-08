/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:58:22 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 23:20:08 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "base.h"

typedef struct		s_info
{
	int				num_of_ph;
	long long		time_dead;
	long long		time_eat;
	long long		time_sleep;
	int				num_eat;
	long long		start_time;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	dead_mutex;
}					t_info;

typedef struct		s_ph
{
	int				id;
	int				is_eat;
	long long		time_last_meal;
	long long		time_dead_limit;
	int				left_fork;
	int				right_fork;
	int				num_eat;
	t_info			*info;
	pthread_mutex_t	ph_mutex;
	pthread_mutex_t eat_mutex;
}					t_ph;

typedef struct		s_manager
{
	t_info			*info;
	t_ph			**phs;
}					t_manager;

#endif
