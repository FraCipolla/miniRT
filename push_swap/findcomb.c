/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:22:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:22:42 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	**ft_new_comb(t_struct *data)
{
	int	**comb;

	comb = (int **) malloc (sizeof(int *) * data->size_a);
	ft_checkmalloc(comb);
	comb[0] = (int *) malloc (sizeof(int));
	ft_checkmalloc(comb[0]);
	comb[0][0] = 1;
	return (comb);
}

int	*ft_clone_add(int *r2, int *len, int nb)
{
	int	*arr;
	int	i;

	arr = (int *) malloc (sizeof(int) * (*len + 1));
	ft_checkmalloc(arr);
	i = 0;
	while (i < *len)
	{
		arr[i] = r2[i];
		i++;
	}
	arr[i] = nb;
	(*len)++;
	return (arr);
}

void	ft_between(int **comb, int num)
{
	int	i;
	int	j;

	i = 0;
	while (comb[i][i] < num)
		i++;
	j = 0;
	while (j < i)
	{
		comb[i][j] = comb[i - 1][j];
		j++;
	}
	comb[i][j] = num;
}

void	ft_findcomb(t_struct *data)
{
	int	**comb;
	int	i;
	int	r;

	comb = ft_new_comb(data);
	r = 1;
	i = ft_findindmin(data->ar_a, data->size_a);
	i++;
	if (i == data->size_a)
		i = 0;
	while (data->ar_a[i] != 1)
	{
		if (data->ar_a[i] > comb[r - 1][r - 1])
			comb[r - 1] = ft_clone_add(comb[r - 1], &r, data->ar_a[i]);
		else
			ft_between(comb, data->ar_a[i]);
		i++;
		if (i == data->size_a)
			i = 0;
	}
	data->ar_best = ft_ardup(comb[r - 1], r);
	data->size_best = r;
	ft_freematrix(comb, r);
}
