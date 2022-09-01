/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:53:39 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/01 16:37:41 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	computeLighting(t_v3 P, t_v3 N, t_data *data, t_obj *closest)
{
	double	i;
	t_v3	L;
	double 	dot_l;
	t_v3	R;
	t_light	*new;

	i = 0.0;
	new = data->light;
	while (new)
	{
		if (new->t == 'A')
			i += new->ratio;
		if (new->t == 'L')
		{
			L = sub_vec(new->pos, P);
			dot_l = dot(N, L);
			if (dot_l > 0)
				i +=(new->ratio * dot_l / (sqrtf(dot(N, N)) * sqrtf(dot(L, L))));
		}
		new = new->next;
	}
	// if (data->dir.pos.vec != NULL)
	// {
	// 	L = data->dir.pos.vec;
	// 	dot_l = dot(N, L);
	// 	if (dot_l > 0)
	// 		i +=(data->dir.bright * dot_l / (sqrtf(dot(N, N)) * sqrtf(dot(L, L))));
	// }
	// if (closest->spec != -1)
	// {
	// 	R = sub_vec(mult_vec_n(mult_vec_n(N, 2), dot(N, L)), L);
	// 	double r_dot_v = dot(R, mult_vec_n(data->cam.dir, -1));
	// 	if (r_dot_v > 0)
	// 	{
	// 		i += data->light.bright * pow(r_dot_v / (norm(R) * norm(mult_vec_n(data->cam.dir, -1))), closest->spec);
	// 	}
	// }
	if (i > 1)
		i =	1;
	return (i);
}