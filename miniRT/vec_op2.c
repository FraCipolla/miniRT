/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 15:06:18 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/04 15:17:33 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_v3	sub_vec(t_v3 v1, t_v3 v2)
{
	t_v3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_v3	mult_vec(t_v3 v1, t_v3 v2)
{
	t_v3	ret;
	
	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return (ret);
}

t_v3	div_vec(t_v3 v1, t_v3 v2)
{
	t_v3	ret;
	
	ret.x = v1.x / v2.x;
	ret.y = v1.y / v2.y;
	ret.z = v1.z / v2.z;
	return (ret);
}

t_v3	mult_vec_n(t_v3 v1, double d)
{
	t_v3	ret;
	
	ret.x = v1.x * d;
	ret.y = v1.y * d;
	ret.z = v1.z * d;
	return (ret);
}

t_v3	cross(t_v3 v1, t_v3 v2)
{
	t_v3	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}