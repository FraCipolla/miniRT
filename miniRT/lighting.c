/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:53:39 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/27 14:20:06 by mcipolla         ###   ########.fr       */
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
	return (i);
}