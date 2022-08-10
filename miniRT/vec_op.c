/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/10 14:09:17 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*normalize(double *v1)
{
	double	*ret;
	double	square;

	ret = malloc(sizeof(double) * 3);
	square = sqrt(doubleDot(v1, v1));
	ret[0] = v1[0] / square;
	ret[1] = v1[1] / square;
	ret[2] = v1[2] / square;
	return (ret);
}

double	get_lenght(double *v1, double *v2)
{
	return (sqrt(doubleDot(v1, v2)));
}

double	doubleDot(double *v1, double *v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

double	*add_vec(double *v1, double *v2)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[0] + v2[0];
	ret[1] = v1[1] + v2[1];
	ret[2] = v1[2] + v2[2];
	return (ret);
}

double	*dim_vec(double *v1, double *v2)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[0] - v2[0];
	ret[1] = v1[1] - v2[1];
	ret[2] = v1[2] - v2[2];
	return (ret);
}

double	*mult_vec(double *v1, double *v2)
{
	double	*ret;
	
	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[0] * v2[0];
	ret[0] = v1[1] * v2[1];
	ret[0] = v1[2] * v2[2];
	return (ret);
}

double	*div_vec(double *v1, double *v2)
{
	double	*ret;
	
	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[0] / v2[0];
	ret[0] = v1[1] / v2[1];
	ret[0] = v1[2] / v2[2];
	return (ret);
}
