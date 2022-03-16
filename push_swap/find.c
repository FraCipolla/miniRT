/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:42:10 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/15 15:42:12 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_min(int *array, int size)
{
	int	min;
	int	i;

	min = array[0];
	i = 1;
	while (i < size)
	{
		if (array[i] < min)
			min = array[i];
		i++;
	}
	return (min);
}

int	ft_max(int *array, int size)
{
	int	max;
	int	i;

	max = array[0];
	i = 1;
	while (i < size)
	{
		if (array[i] > max)
			max = array[i];
		i++;
	}
	return (max);
}

int		ft_findind(int nb, int *array)
{
	int	i;

	i = 0;
	while (array[i] != nb)
		i++;
	return (i);
}

int		ft_findindmin(int *array, int size)
{
	return (ft_findind(ft_min(array, size), array));
}

int		ft_findindmax(int *array, int size)
{
	return (ft_findind(ft_max(array, size), array));
}
