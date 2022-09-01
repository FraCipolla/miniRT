/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:26:22 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/01 18:14:37 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_light	*last_light(t_light *light)
{
	if (!light)
		return (NULL);
	while (light->next)
		light = light->next;
	return (light);
}

void	add_light(char	**args, t_data *data)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	new->t = args[0][0];
	if (args[0][0] == 'A')
		new->ratio = atof(args[1]);
	else
		new->ratio = atof(args[2]);
	if (args[0][0] == 'A')
		new->RGB = ret_vec(args[2]);
	else
		new->RGB = ret_vec(args[3]);
	new->next = NULL;
	if (new == NULL)
		return ;
	if (data->light == NULL)
		data->light = new;
	else
		last_light(data->light)->next = new;
}

t_obj	*last_obj(t_obj	*obj)
{
	if (!obj)
		return (NULL);
	while (obj->next)
		obj = obj->next;
	return (obj);
}

void	add_obj(char **args, t_data *data)
{
	t_obj	*new;
	
	new = malloc(sizeof(t_obj));
	new->id = ft_strdup(args[0]);
	new->pos = ret_vec(args[1]);
	if (ft_strcmp(new->id, "pl") == 0)
	{
		new->ori = ret_vec(args[2]);
		new->RGB = ret_vec(args[3]);
	}
	else if (ft_strcmp(new->id, "sp") == 0)
	{
		new->r = atof(args[2]) / 2;
		new->RGB = ret_vec(args[3]);
		new->spec = atof(args[4]);
	}
	else if (ft_strcmp(new->id, "cy") == 0)
	{
		new->ori = ret_vec(args[2]);
		new->r = atof(args[3]);
		new->h = atof(args[4]);
		new->RGB = ret_vec(args[5]);
		if (args[6])
			new->spec = atof(args[6]);
	}
	new->next = NULL;
	if (new == NULL)
		return ;
	if (data->obj == NULL)
		data->obj = new;
	else
		last_obj(data->obj)->next = new;
}
