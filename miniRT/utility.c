/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:26:46 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/30 13:53:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (-1);
}

double	*ret_vec(char *args)
{
	double	*vec;
	char	**xyz;

	vec = malloc(sizeof(double) * 3);
	xyz = ft_split(args, ',');
	vec[0] = atof(xyz[0]);
	vec[1] = atof(xyz[1]);
	vec[2] = atof(xyz[2]);
	return (vec);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tab;

	i = 0;
	while (s1[i])
		i++;
	tab = (char *)malloc(sizeof(char) * i + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
