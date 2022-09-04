/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:04:03 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/04 18:47:54 by mcipolla         ###   ########.fr       */
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

void	parse_buff(char *buff, t_data *data)
{
	char	**args;
	char	**args2;

	args = ft_split(buff, ' ');
	args2 = ft_split(buff, ' ');
	if (args[0][0] == 'C')
	{
		if (camera_init(args, &data->cam) == -1)
			exit(0);
	}
	else
	{
		if (ft_strcmp(args[0], "pl") == 0 ||
			ft_strcmp(args[0], "sp") == 0 ||
			ft_strcmp(args[0], "cy") == 0)
			add_obj(args2, data);
		else
			add_light(args2, data);
	}
	free(args);
	free(args2);
}

int	ft_init(t_data *data, int fd)
{
	char	*buff;
	char	*to_matrix;
	int 	i;
	
	to_matrix = NULL;
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
		return(ft_error("Invalid Arguments\n"));
	i = -1;
	while (data->matrix[++i])
	{
		parse_buff(data->matrix[i], data);
		printf("%s\n", data->matrix[i]);
	}
	return (1);
}
