/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcomb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:42:59 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/15 18:02:26 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//void	ft_copyextend(int **comb, int nb, int *lines)		
//{
//	comb[*lines] = ft_ardup(comb[*lines - 1], *lines + 1);
//	comb[*lines][*lines] = nb;
//	(*lines)++;
//}

//void	ft_copyexdel(int **comb, int nb)
//{
//	int	i;
//	int	*ar;

//	i = 0;
//	while (comb[i][i] < nb)
//		i++;
//	ar = ft_ardup(comb[i - 1], i + 1);
//	free(comb[i - 1]);
//	comb[i - 1] = ar;
//	comb[i - 1][i] = nb;
//	printf("\n");
//	ft_printarray(comb[i - 1], i + 1);
//}

//int	*ft_findcomb(t_struct *data)
//{
//	int		**comb;
//	int		lines;
//	int		i;

//	comb = (int **) malloc (sizeof(int *) * data->size_a);
//	ft_checkmalloc(comb);
//	i = ft_findindmin(data->ar_a, data->size_a);
//	comb[0] = (int *) malloc (sizeof(int) * 1);
//	ft_checkmalloc(comb[0]);
//	comb[0][0] = data->ar_a[i];
//	lines = 1;
//	//ft_printarray(comb[lines - 1], lines);
//	i += 1;
//	if (i == data->size_a)
//			i = 0;
//	while (data->ar_a[i] != ft_min(data->ar_a, data->size_a))
//	{
//		if (data->ar_a[i] > comb[lines - 1][lines - 1])
//			ft_copyextend(comb, data->ar_a[i], &lines);
//		else
//			ft_copyexdel(comb, data->ar_a[i]);
//		i++;
//		printf("\n");
//		ft_printarray(comb[lines - 1], lines);
//		printf("\n%d\n", lines);
//		if (i == data->size_a)
//			i = 0;
//	}
//	//printf("\n");
//	//ft_printarray(comb[lines - 1], lines);
//	return (comb[lines]);
//}


void	ft_findcomb(t_struct *data)
{
	int	**comb;
	int	i;
	int	r;

	comb = (int **) malloc (sizeof(int *) * data->size_a);
	ft_checkmalloc(comb);
	comb[0] = (int *) malloc (sizeof(int));
	ft_checkmalloc(comb[0]);
	comb[0][0] = 1;
	r = 1;
	i = ft_findindmin(data->ar_a, data->size_a);
	i++;
	if (i == data->size_a)
		i = 0;
	while (data->ar_a[i] != 1)
	{
		if (data->ar_a[i] > comb[r - 1][r - 1])
		{
			comb[r] = ft_clone_add(comb[r - 1], r, data->ar_a[i]);
			r++;
			//ft_printarray(comb[r - 1], r);
		}
		else
			ft_between(comb, data->ar_a[i]);
		i++;
		if (i == data->size_a)
			i = 0;
	}
	data->best = comb[r - 1];
	data->size_best = r;
}

int	*ft_clone_add(int *r2, int len, int nb)
{
	int	*arr;
	int	i;

	arr = (int *) malloc (sizeof(int) * (len + 1));
	ft_checkmalloc(arr);
	i = 0;
	while (i < len)
	{
		arr[i] = r2[i];
		i++;
	}
	arr[i] = nb;
	return (arr);
}

void	ft_between(int **comb, int num)
{
	int i;
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
