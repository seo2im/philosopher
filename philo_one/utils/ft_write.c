/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:35:44 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:42:16 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		ft_write(const char *str)
{
	int len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int		ft_writen(const char *str)
{
	int len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	write(1, str, len);
	write(1, "\n", 1);
	return (len + 1);
}
