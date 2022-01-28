/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/28 17:36:18 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*conv_dst;
	char	*conv_src;

	conv_src = (char *)src;
	conv_dst = (char *)dst;
	i = 0;
	while (i < len)
	{
		conv_dst[i] = conv_src[i];
		i++;
	}
	return (dst);
}