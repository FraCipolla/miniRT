/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:53:39 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/29 11:25:07 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	computeLighting(double *P, double *N, t_data *data, t_obj *closest)
{
	double	i;
	double	*L;
	double 	dot_l;
	double	*R;

	i = 0.0;
	i += data->ambLight.ratio;
	if (data->light.pos.vec != NULL)
	{
		L = dim_vec(data->light.pos.vec, P);
		dot_l = dot(N, L);
		if (dot_l > 0)
			i +=(data->light.bright * dot_l / (sqrtf(dot(N, N)) * sqrtf(dot(L, L))));
	}
	if (data->dir.pos.vec != NULL)
	{
		L = data->dir.pos.vec;
		dot_l = dot(N, L);
		if (dot_l > 0)
			i +=(data->dir.bright * dot_l / (sqrtf(dot(N, N)) * sqrtf(dot(L, L))));
	}
	// if (closest->specular != -1)
	// {
	// 	R = malloc(sizeof(double) * 3);
	// 	R = dim_vec(mult_vec_d(mult_vec_d(N, 2), dot(N, L)), L);
	// 	double r_dot_v = dot(R, data->cam.dir.vec);
	// 	if (r_dot_v > 0)
	// 	{
	// 		i += data->light.bright * pow(r_dot_v / (sqrtf(dot(R, R)) * sqrtf(dot(data->cam.dir.vec, data->cam.dir.vec))), closest->specular);
	// 	}
	// }
	return (i);
}