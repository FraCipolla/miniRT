/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 14:36:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/04 18:46:48 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_mat4x4	look_at(t_v3 origin, t_v3 dir)
{
	t_v3		check;
	t_v3		up_tmp;
	t_v3		forward;
	t_v3		right;
	t_v3		up;

	check = normalize(dir);
	if (check.x == 0.0 && fabs(check.y) == 1.0 && check.z == 0.0)
	{
		forward = normalize(mult_vec_n(sub_vec(origin, dir), -1));
		right = ret_vec("1,0,0");
	}
	else
	{
		up_tmp = ret_vec("0,1,0");
		forward = normalize(mult_vec_n(sub_vec(origin, dir), -1));
		right = cross(up_tmp, forward);
	}
	up = cross(forward, right);
	return (mat4x4(origin, forward, right, up));
}

int	camera_init(char **args, t_cam *cam)
{
	cam->pos = ret_vec(args[1]);
	cam->ori = normalize(ret_vec(args[2]));
	cam->FOV = atof(args[3]);
	if (cam->FOV <= 0 || cam->FOV >= 180)
		return(ft_error("Range of FOV invalid"));
	cam->view_range = tan((cam->FOV * 0.5) * (M_PI / 180));
	cam->world = look_at(cam->pos, add_vec(cam->pos, cam->ori));
	return (0);
}