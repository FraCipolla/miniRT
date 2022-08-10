/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/10 14:23:41 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	add_sphere(char **args, t_data *data)
{
	t_sphere	*new;
	t_sphere	*tmp;
	
	new = malloc(sizeof(t_sphere));
	new->pos.vec = ret_vec(args[1]);
	new->diam = atof(args[2]);
	new->colors.vec = ret_vec(args[3]);
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

int	add_plane(char **args, t_data *data)
{
	t_plane	*new;
	t_plane	*tmp;
	
	new = malloc(sizeof(t_plane));
	new->pos.vec = ret_vec(args[1]);
	new->ori.vec = ret_vec(args[2]);
	new->colors.vec = ret_vec(args[3]);
	new->next = NULL;
	if (data->plane == NULL)
		data->plane = new;
	else
	{
		tmp = data->plane;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	add_cylinder(char **args, t_data *data)
{
	t_cylind	*new;
	t_cylind	*tmp;
	
	new = malloc(sizeof(t_cylind));
	new->pos.vec = ret_vec(args[1]);
	new->ori.vec = ret_vec(args[2]);
	new->diam = atof(args[3]);
	new->height = atof(args[4]);
	new->colors.vec = ret_vec(args[5]);
	new->next = NULL;
	if (data->cylinder == NULL)
		data->cylinder = new;
	else
	{
		tmp = data->cylinder;
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
	if (ft_strcmp(args[0], "pl") == 0)
		return (add_plane(args, data));
	if (ft_strcmp(args[0], "cy") == 0)
		return (add_cylinder(args, data));
	return (1);
}