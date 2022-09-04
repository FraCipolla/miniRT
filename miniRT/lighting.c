/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 13:53:39 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/04 19:16:49 by mcipolla         ###   ########.fr       */
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
	double	max;

	i = 0.0;
	new = data->light;
	while (new)
	{
		if (new->t == 'A')
			i += new->ratio;
		else
		{
			if (new->t == 'L')
				L = sub_vec(new->pos, P);
			else
				L = new->pos;
			double	n_dot_l = dot(N, L);
			if (n_dot_l > 0)
				i += new->ratio * n_dot_l / (norm(L) * norm(N));
			if (closest->spec != -1)
			{
				R = sub_vec(mult_vec_n(mult_vec_n(N, 2), dot(N, L)), L);
				double	r_dot_v = dot(R, mult_vec_n(data->ray.dir, -1));
				if (r_dot_v > 0)
					i += new->ratio * pow(r_dot_v / (norm(R) * norm(mult_vec_n(data->ray.dir, -1))), closest->spec);
			}
		}
		new = new->next;
	}
	if (i > 1)
		i =	1;
	return (i);
}