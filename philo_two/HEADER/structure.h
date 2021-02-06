/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:52:51 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 17:27:02 by seolim           ###   ########.fr       */
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

typedef struct		s_ph
{
	int				id;
	t_info			*info;
	pthread_t		*thread;
	sem_t			*last_meal_sem; 
	struct timeval	*last_meal_time;
	sem_t			*message;
	sem_t			*forks;
	sem_t			*eat_available; // TODO : point!
	int				num_of_eat;
}					t_ph;

typedef struct		s_manager
{
	t_info			*info;
	t_ph			**phs;
	sem_t			*message;
	sem_t			*forks;
	sem_t			*eat_available;
}					t_manager;


#endif
