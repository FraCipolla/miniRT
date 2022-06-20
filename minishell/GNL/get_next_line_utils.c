/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:16:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/20 16:56:36 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr(const char *s, char c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			break ;
		s++;
	}
	if (*s != c)
		return (0);
	return (1);
}
