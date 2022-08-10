/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:04:03 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/08 19:44:49 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_arg(t_data *data)
{
	int	A;
	int	C;
	int	L;
	int	i;

	i = -1;
	A = 0;
	C = 0;
	L = 0;
	while (data->martix[++i])
	{
		if (data->martix[i][0] == 'A')
			A++;
		if (data->martix[i][0] == 'C')
			C++;
		if (data->martix[i][0] == 'L')
			L++;
	}
	if (A != 1 || C != 1 || L != 1)
		return (0);
	return (1);
}

int	parse_buff(char *buff, t_data *data)
{
	char **args;

	args = ft_split(buff, ' ');
	if (args[0][0] == 'A')
	{
		data->ambLight.ratio = ft_atof(args[1]);
		data->ambLight.colors.vec = ret_vec(args[2]);
	}
	else if (args[0][0] == 'C')
	{
		data->cam.pos.vec = ret_vec(args[1]);
		data->cam.ori.vec = ret_vec(args[2]);
		data->cam.FOV = ft_atof(args[3]);
	}
	else if (args[0][0] == 'L')
	{
		data->light.pos.vec = ret_vec(args[1]);
		data->light.bright = ft_atof(args[2]);
		data->light.colors.vec = ret_vec(args[3]);
	}
	else
		parse_primitive(buff, data);
	free(args);
	return (1);
}
