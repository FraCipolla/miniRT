/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/07 15:06:43 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vectorDot(vector *v1, vector *v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

t_vec3	add_vec(vector *v1, vector *v2)
{
	return (v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

t_vec3	dim_vec(vector *v1, vector *v2)
{
	return (v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

t_vec3	mult_vec(vector *v1, vector *v2)
{
	return (v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}
