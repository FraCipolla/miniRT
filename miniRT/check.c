/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:04:03 by mcipolla          #+#    #+#             */
/*   Updated: 2022/08/30 13:53:08 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_arg(t_data *data)
{
	int	A;
	int	C;
	int	L;
	int	i;

	i = -1;
	A = 0;
	C = 0;
	L = 0;
	while (data->matrix[++i])
	{
		if (data->matrix[i][0] == 'A')
			A++;
		if (data->matrix[i][0] == 'C')
			C++;
		if (data->matrix[i][0] == 'L')
			L++;
	}
	if (A != 1 || C != 1 || L != 1)
		return (0);
	return (1);
}

int	parse_buff(char *buff, t_data *data)
{
	char **args;

	args = ft_split(buff, ' ');
	if (args[0][0] == 'A')
	{
		data->ambLight.ratio = atof(args[1]);
		data->ambLight.RGB = ret_vec(args[2]);
	}
	else if (args[0][0] == 'C')
	{
		data->cam.pos.vec = ret_vec(args[1]);
		data->cam.ori.vec = ret_vec(args[2]);
		data->cam.FOV = atof(args[3]);
	}
	else if (args[0][0] == 'L')
	{
		data->light.pos.vec = ret_vec(args[1]);
		data->light.bright = atof(args[2]);
		data->light.RGB = ret_vec(args[3]);
	}
	else if (args[0][0] == 'D')
	{
		data->dir.bright = atof(args[1]);
		data->dir.pos.vec = ret_vec(args[2]);
		data->dir.RGB = ret_vec(args[3]);
	}
	else
		parse_primitive(buff, data);
	free(args);
	return (1);
}

int	ft_init(t_data *data, int fd)
{
	char	*buff;
	char	*to_matrix;
	int 	i;
	
	to_matrix = NULL;
	data->dir.pos.vec = NULL;
	data->obj_size = 0;
	data->obj = (t_obj*)malloc(sizeof(t_obj) * 20);
	data->t = malloc(sizeof(double) * 2);
	while (fd > 0)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break ;
		to_matrix = ft_strjoin(to_matrix, buff);
		free (buff);
	}
	data->matrix = ft_split(to_matrix, '\n');
	if (check_arg(data) == 0)
		ft_error("Invalid Arguments\n");
	i = -1;
	while (data->matrix[++i])
	{
		parse_buff(data->matrix[i], data);
		printf("%s\n", data->matrix[i]);
	}
	return (1);
}
