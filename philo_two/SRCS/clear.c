/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:18:14 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:19:48 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	ft_ph_free(t_ph **phs)
{
	int	i;

	i = -1;
	while (phs[++i])
	{
		if (phs[i]->info)
			free(phs[i]->info);
		if (phs[i]->thread)
			free(phs[i]->thread);
		free(phs[i]);
	}
	free(phs);
}

void	clear_manager(t_manager *manager)
{
	if (manager->info)
		free(manager->info);
	if (manager->phs)
		ft_ph_free(manager->phs);
}
