/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_name.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:30:57 by seolim            #+#    #+#             */
/*   Updated: 2021/02/10 14:31:27 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

char		*sem_name(char *str, int id)
{
	char	*name;
	char	*id_str;
	int		i;
	int		j;

	id_str = ft_itoa(id);
	if (!(name =
		malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(id_str) + 1))))
		return (NULL);
	i = -1;
	j = -1;
	while (str[++j])
		name[++i] = str[j];
	j = -1;
	while (id_str[++j])
		name[++i] = str[j];
	name[++i] = 0;
	free(id_str);
	return (name);
}
