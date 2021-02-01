/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosoper.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:48:19 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 17:51:59 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPER_H
# define PHILOSOPER_H
# include <sys/stat.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include "utils.h"
# define EAT 1
# define SLEEP 2
# define THINK 3
# define FORK 4
# define DEAD 5
# define END 6

typedef struct		s_manager
{
	int				ph_num;
	long			dead_time;
	long			eat_time;
	long			sleep_time;
	int				must_eat_num;

	long			start_time;
	struct s_ph		*ph_list;

	sem_t			*forks;
	sem_t			*output;
	int				end_count;
}					t_manager;

typedef struct		s_ph
{
	int				id;
	int				left_fork;
	int				right_fork;
	long			dead_limit;
	int				eat_count;
	int				is_end;

	t_manager		*manager;
	sem_t			*live;
}					t_ph;

int					get_fork(t_ph *philosoper);
int					put_fork(t_ph *philosoper);
int					message(t_ph *philosoper, int kind);
int					init_manager(t_manager *manager, char *argv[], int argc);
int					clear(t_manager *manager);
void				eating(t_ph *philosoper);

#endif
