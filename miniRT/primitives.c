/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/07 18:13:05 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_sphere(char **args, t_data *data)
{
	t_sphere	*new;
	t_sphere	*tmp;
	
	new = malloc(sizeof(t_sphere));
	new->pos = ret_vec(args[1]);
	new->diam = ft_atof(args[2]);
	new->colors = ret_vec(args[3]);
	new->next = NULL;
	if (data->sphere == NULL)
		data->sphere = new;
	else
	{
		tmp = data->sphere;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	parse_primitive(char *buff, t_data *data)
{
	char **args;

	args = ft_split(buff, ' ');
	if (ft_strcmp(args[0], "sp") == 0)
		return (add_sphere(args, data));
	// if (ft_strcmp(args[0], "pl") == 0)
	// 	return (add_plane(args, data));
	// if (ft_strcmp(args[0], "cy") == 0)
	// 	return (add_cylinder(args, data));
	return (1);
}