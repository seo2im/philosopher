/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:58:22 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 22:21:26 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include "base.h"

struct s_manager;

typedef struct		s_ph
{
	int				id;
	int				is_eat;
	long long		time_last_meal;
	long long		time_dead_limit;
	int				left_fork;
	int				right_fork;
	int				num_eat;
	struct s_manager*manager;
	pthread_mutex_t	ph_mutex;
	pthread_mutex_t eat_mutex;
}					t_ph;

typedef struct		s_manager
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
	t_ph			*phs;
}					t_manager;


#endif
