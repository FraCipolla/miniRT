/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:24:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:24:43 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	*ft_ardup(int *ar, int size)
{
	int	*ptr;
	int	i;

	ptr = (int *) malloc (sizeof(int) * size);
	ft_checkmalloc(ptr);
	i = 0;
	while (i < size)
	{
		ptr[i] = ar[i];
		i++;
	}
	return (ptr);
}

void	ft_freematrix(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_sort_ar(int *ar, int size)
{
	int	i;
	int	flag;

	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ar[i] > ar[i + 1])
			{
				ft_swap(ar + i, ar + (i + 1), size);
				flag = 0;
			}
			i++;
		}
	}
}

// void	ft_printarray(int *ar, int size)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 	{
// 		ft_printf("%d\n", ar[i]);
// 		i++;
// 	}
// }
