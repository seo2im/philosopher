/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 23:37:23 by seolim            #+#    #+#             */
/*   Updated: 2021/02/06 23:37:28 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_ph_free(t_ph **phs)
{
	int	i;

	i = -1;
	while (phs[++i])
	{
		if (phs[i]->info)
			free(phs[i]->info);
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
