/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 17:42:28 by seolim            #+#    #+#             */
/*   Updated: 2021/02/08 20:11:13 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "base.h"

int			ft_atoi(const char *str);
int			ft_strlen(char *str);
int			ft_write(int fd, char *str);
int			ft_write_n(int fd, char *str);
long long	ft_gettime(void);
void		ft_usleep(long long n);
char		*ft_itoa(int n);

#endif
