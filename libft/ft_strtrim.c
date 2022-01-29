/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:36:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/29 17:20:29 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_set(char c, char const *set)
{
	int	x;

	x = 0;
	while (set[x])
	{
		if (set[x] == c)
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	int				size;
	unsigned int	len;
	char			*tab;
	int				c;

	i = 0;
	len = ft_strlen(s1) - 1;
	while (check_set(s1[i], set) == 1 && s1[i])
		i++;
	if (s1[i] == '\0')
	{
		tab = (char *)malloc(sizeof(char) * 1);
		if (!tab)
			return (NULL);
		tab[0] = 0;
		return (tab);
	}		
	while (check_set(s1[len], set) == 1)
		len--;
	size = len - i;
	tab = (char *)malloc(sizeof(char) * size + 2);
	if (!tab)
		return (NULL);
	c = 0;
	while (i <= len)
	{
		tab[c] = s1[i];
		c++;
		i++;
	}
	tab[c] = '\0';
	return (tab);
}