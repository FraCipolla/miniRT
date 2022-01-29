/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/29 17:16:15 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*conv_s1;
	unsigned char	*conv_s2;

	conv_s1 = (unsigned char *)s1;
	conv_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n -1 && conv_s1[i] == conv_s2[i])
		i++;
	return (conv_s1[i] - conv_s2[i]);
}