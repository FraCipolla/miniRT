/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:22:08 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:22:35 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_checkmalloc(void *ptr)
{
	if (ptr == NULL)
		ft_error();
}

int	ft_order(int *ar, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (ar[i] > ar[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_max(char *str)
{
	long long int	nb;
	int				i;
	int				sign;

	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = 0;
	while (str[i] != '\0')
	{
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	nb *= sign;
	if (nb > 2147483647 || nb < -2147483648)
		ft_error();
}

int	ft_multi_check(char **matrix, int size)
{
	int	row;
	int	col;

	row = 0;
	while (row < size)
	{
		col = 0;
		if (matrix[row][col] == '-' || matrix[row][col] == '+')
			col += 1;
		if (matrix[row][col] == '\0')
			return (0);
		while (matrix[row][col] != '\0')
		{
			if (ft_isdigit(matrix[row][col]) == 0)
				return (0);
			col++;
		}
		row++;
	}
	return (1);
}

int	ft_checkfordoubles(int *ar, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ar[i] == ar[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
