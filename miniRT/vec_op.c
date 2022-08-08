/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/08 19:08:17 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	get_lenght(double *v1, double *v2)
{
	return (sqrt(doubleDot(v1, v2)));
}

double	doubleDot(double *v1, double *v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

// double	add_vec(double *v1, double *v2)
// {
// 	return (v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
// }

double	*dim_vec(double *v1, double *v2)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[0] - v2[0];
	ret[1] = v1[1] - v2[1];
	ret[2] = v1[2] - v2[2];
	return (ret);
}

// double	mult_vec(double *v1, double *v2)
// {
// 	return (v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
// }