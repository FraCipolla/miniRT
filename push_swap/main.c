/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:23:25 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:23:25 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_go_away(t_struct *data, int x)
{
	int	nb;

	nb = data->ar_a[x];
	while (data->ar_a[0] != nb)
	{
		if (x <= data->size_a / 2)
			ft_rotate_a(data);
		else
			ft_rev_rotate_a(data);
	}
	ft_push_b(data);
}

void	ft_sep(t_struct *data)
{
	int	i;
	int	average;
	int	*ar;

	ar = data->ar_a;
	average = data->size_a / 4;
	while (data->size_a != data->size_best && average != 0)
	{
		i = 0;
		while (i < data->size_a)
		{
			if (ft_findind(ar[i], data->ar_best, data->size_best) == -1)
			{
				if (ar[i] <= average || average < 3)
				{
					ft_go_away(data, i);
					i = -1;
				}
			}
			i++;
		}
		average += (data->size_a + data->size_b) / 4;
	}
}

void	ft_resolve(t_struct *data)
{
	int	max_size;
	int	*ara;

	ara = data->ar_a;
	max_size = data->size_a;
	data->ar_b = (int *) malloc (sizeof(int) * max_size);
	ft_checkmalloc(data->ar_b);
	data->size_b = 0;
	if (ft_order(data->ar_a, data->size_a) == 0)
	{
		if (ara[0] == 1 || ara[1] == 2 || ara[2] == 3)
			if (ara[2] != 5 && ara[0] != 4)
				ft_swap_a(data->ar_a, data->size_a);
		ft_findcomb(data);
		ft_sep(data);
		free(data->ar_best);
		while (data->size_b != 0)
			ft_brainfuck(data);
		if (ft_findind(1, data->ar_a, data->size_a) <= data->size_a / 2)
			while (data->ar_a[0] != 1)
				ft_rotate_a(data);
		else
			while (data->ar_a[0] != 1)
				ft_rev_rotate_a(data);
	}
}

int	*ft_trasformer(int *ar, int size)
{
	int	*temp;
	int	*new;
	int	i;
	int	j;

	new = ft_ardup(ar, size);
	temp = (int *) malloc (sizeof(int) * size);
	ft_checkmalloc(temp);
	ft_sort_ar(new, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (new[i] != ar[j])
			j++;
		temp[j] = i + 1;
		i++;
	}
	free(ar);
	free(new);
	return (temp);
}

int	main(int argc, char *argv[])
{
	t_struct	data;

	if (argc <= 1)
		return (0);
	if (argc == 2)
		data.ar_a = ft_mono_init(argv[1], &data.size_a);
	else
	{
		argc -= 1;
		if (ft_multi_check(&argv[1], argc) == 0)
			ft_error();
		data.ar_a = ft_multi_init(&argv[1], argc);
		data.size_a = argc;
	}
	if (ft_checkfordoubles(data.ar_a, data.size_a) == 0)
		ft_error();
	data.ar_a = ft_trasformer(data.ar_a, data.size_a);
	ft_resolve(&data);
	free(data.ar_a);
	free(data.ar_b);
	return (0);
}
