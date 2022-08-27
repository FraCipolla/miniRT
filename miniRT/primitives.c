/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/27 18:07:50 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_sphere(char **args, t_data *data)
{
	int	size;

	size = data->obj_size;
	data->obj[size].id = ft_strdup("sp");
	data->obj[size].pos.vec = ret_vec(args[1]);
	data->obj[size].diam = atof(args[2]);
	data->obj[size].RGB = ret_vec(args[3]);
	if (args[4] != NULL)
		data->obj[size].specular = atof(args[4]);
	else
		data->obj[size].specular = -1;
	data->obj_size += 1;
	return (0);
}

int	add_plane(char **args, t_data *data)
{
	int	size;

	size = data->obj_size;
	data->obj[size].id	= ft_strdup("pl");
	data->obj[size].pos.vec = ret_vec(args[1]);
	data->obj[size].ori.vec = ret_vec(args[2]);
	data->obj[size].RGB = ret_vec(args[3]);
	return (0);
}

int	add_cylinder(char **args, t_data *data)
{
	int	size;

	size = data->obj_size;
	data->obj[size].id	= ft_strdup("pl");
	data->obj[size].pos.vec = ret_vec(args[1]);
	data->obj[size].ori.vec = ret_vec(args[2]);
	data->obj[size].diam = atof(args[3]);
	data->obj[size].height = atof(args[4]);
	data->obj[size].RGB = ret_vec(args[5]);
	return (0);
}

int	parse_primitive(char *buff, t_data *data)
{
	char **args;

	args = ft_split(buff, ' ');
	if (ft_strcmp(args[0], "sp") == 0)
		return (add_sphere(args, data));
	if (ft_strcmp(args[0], "pl") == 0)
		return (add_plane(args, data));
	if (ft_strcmp(args[0], "cy") == 0)
		return (add_cylinder(args, data));
	return (1);
}