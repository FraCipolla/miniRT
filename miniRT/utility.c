/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:26:46 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/08 19:44:18 by mcipolla         ###   ########.fr       */
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
	vec[0] = ft_atof(xyz[0]);
	vec[1] = ft_atof(xyz[1]);
	vec[2] = ft_atof(xyz[2]);
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
