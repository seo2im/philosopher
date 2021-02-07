/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:52:10 by seolim            #+#    #+#             */
/*   Updated: 2021/02/07 18:02:56 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "base.h"
# include "structure.h"

int		ft_strlen(char *str);
int		ft_error(char *message, int code);
int		ft_write(char *str);
int		ft_write_n(char *str);
int		ft_atoi(const char *str);
char	*ft_itoa(long n);
long	ft_time(struct timeval *time);
void	ft_usleep(unsigned int n);


#endif
