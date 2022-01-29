/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:36:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/01/29 18:00:03 by mcipolla         ###   ########.fr       */
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

	i = 0;
	len = ft_strlen(s1) - 1;
	while (check_set(s1[i], set) == 1 && s1[i])
		i++;
	if (s1[i] == '\0')
		tab = (char *)malloc(sizeof(char) * 1);
	else
	{
		while (check_set(s1[len], set) == 1)
			len--;
		size = len - i;
		tab = (char *)malloc(sizeof(char) * size + 2);
	}
	if (!tab)
		return (NULL);
	size = 0;
	while (i <= len)
		tab[size++] = s1[i++];
	tab[size] = '\0';
	return (tab);
}
