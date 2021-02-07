/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_forks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 22:29:37 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:06:24 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static t_fork	*init_fork()
{
	t_fork	*fork;

	if (!(fork = malloc(sizeof(t_fork))))
		return (NULL);
	if (!(fork->mutex = malloc(sizeof(pthread_mutex_t))))
	{
		free(fork);
		return (NULL);
	}
	if (pthread_mutex_init(fork->mutex, NULL))
	{
		free(fork->mutex);
		free(fork);
		return (NULL);
	}
	return (fork);
}

void			set_fork(t_ph **phs)
{
	t_fork	*fork;
	int		i;

	fork = init_fork();
	fork->nb_last = 0;
	i = -1;
	while (phs[++i])
	{
		phs[i]->left_fork = fork;
		if (phs[i + 1] != NULL)
		{
			fork = init_fork();
			phs[i]->right_fork = fork;
		}
		else
			phs[i]->right_fork = phs[0]->left_fork;
	}
}
