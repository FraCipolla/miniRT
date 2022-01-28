/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:36:07 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/28 18:16:13 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	unsigned int	i;

	i = 0;
	tab = (char*)malloc(sizeof(*s) * (len + 1));
	if (!tab)
		return(NULL);
	while(i <= len)
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	tab[i] = 0;
	return (tab);
}