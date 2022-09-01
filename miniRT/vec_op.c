/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/01 18:22:16 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	dot(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	norm(t_v3 v1)
{
	return (sqrtf(dot(v1, v1)));
}

t_v3	add_vec(t_v3 v1, t_v3 v2)
{
	t_v3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_v3	normalize(t_v3 v1)
{
	t_v3	ret;
	double	magnitude;

	magnitude = norm(v1);
	ret.x = v1.x / magnitude;
	ret.y = v1.y / magnitude;
	ret.z = v1.z / magnitude;
	return (ret);
}
