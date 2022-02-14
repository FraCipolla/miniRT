/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:51:02 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/13 14:50:21 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <strings.h>
# include <stddef.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

char *get_next_line(int fd);
int	ft_strlen(char *s);

#endif