/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/30 13:55:28 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	*sub_vec(double *v1, double *v2)
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

double	*mult_vec_n(double *v1, double d)
{
	double	*ret;
	
	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[0] * d;
	ret[1] = v1[1] * d;
	ret[2] = v1[2] * d;
	return (ret);
}

double	*cross(double *v1, double *v2)
{
	double	*ret;

	ret = malloc(sizeof(double) * 3);
	ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
	ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
	ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return (ret);
}