/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:54 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/28 18:02:44 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t src_len;

	i = 0;
	src_len = ft_strlen(src);
	while (dst[i] && src[i] && i < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	dst[dstsize] = 0;
	return (src_len);
}