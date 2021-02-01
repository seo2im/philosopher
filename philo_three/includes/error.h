/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seolim <seolim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 16:57:56 by seolim            #+#    #+#             */
/*   Updated: 2021/02/01 16:58:03 by seolim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include <unistd.h>
# define SUCCESS 1
# define FAIL 0
# define ERROR -1

int	ft_error(char *str, int code);

#endif
