/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:42:19 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/21 16:54:02 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

 void	ft_go_away(t_struct *data, int x)
 {
 	int	i;
 	int	nb;

 	nb = data->ar_a[x];
 	i = 0;
 	while(data->ar_a[0] != nb)
 	{
 		if (x <= data->size_a / 2)
 			ft_rotate_a(data);
 		else if (x > data->size_a / 2)
 			ft_rev_rotate_a(data);
 	}
 	ft_push_b(data);
 }

 void	ft_sep(t_struct *data)
 {
 	int	i;
 	int	j;
 	int	flag;

 	i = 0;
 	while (i < data->size_a)
 	{
 		flag = 0;
 		j = 0;
 		while (j < data->size_best)
 		{
 			if(data->best[j] == data->ar_a[i])
 				flag = 1;
 			j++;
 		}
 		if (flag == 0)
 		{
 			ft_go_away(data, i);
 			i = -1;
 		}
 		i++;
 	}
}

int	ft_order_b(int *ar, int size)
{
	int	i;

	i = 0;
	if (size == 0)
		return (1);
	while (i < size - 1)
	{
		if (ar[i] < ar[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	ft_order_a(int *ar, int size)
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

static int	ft_findmax(t_struct *data)
{
	int	i;
	int	res;

	i = - 1;
	res = 0;
	while (i++ < data->size_b)
	{
		if (data->ar_b[i] > res)
			res = data->ar_b[i];
	}
	return (res);
}

void	ft_brainfuck(t_struct *data)
{
	int	size;
	int	max;
	int	x;

	max = data->size_a - 1;
	x = 9;
	size = max;
	while (data->size_b < size / 10)
	{
		if (data->ar_a[0] > (size / 10) * x)
			ft_push_b(data);
		else
			ft_rotate_a(data);
	}
	if (data->size_b < 3)
	{
		while(ft_order_a(data->ar_a, data->size_a) == 0)
			{
				if (data->ar_a[0] > data->ar_a[1])
					ft_swap_a(data->ar_a);
				else if (data->ar_a[0] > data->ar_a[data->size_a - 1])
					ft_rotate_a(data);
				else
			 		ft_rev_rotate_a(data);
			}
		while (data->size_b > 0)
			{
				if (data->ar_b[0] == data->ar_a[0] - 1)
					ft_push_a(data);
				else
					ft_rotate_b(data);
			}
	}
	while (data->size_b > 0)
	{
		while (ft_order_a(data->ar_a, data->size_a) == 0)
		{
			while (ft_order_b(data->ar_b, data->size_b) == 0)
			{
				if (data->ar_b[data->size_b - 1] == ft_findmax(data))
					ft_rev_rotate_b(data);
				if (data->ar_b[0] == ft_findmax(data))
					ft_push_a(data);
				else if (data->ar_b[0] < data->ar_b[1])
					ft_swap_b(data->ar_b);
				else if (data->ar_b[0] < data->ar_b[data->size_b - 1])
					ft_rotate_b(data);
				else
			 		ft_rev_rotate_b(data);
			}
			while (data->size_b > 0)
				ft_push_a(data);
			x = x - 1;
			if (x > 0)
			{
				while (data->size_b < size / 10)
				{
					if (data->ar_a[0] > (size / 10) * x && data->ar_a[0] <= (size/ 10) * (x + 1))
						ft_push_b(data);
					else
						ft_rotate_a(data);
				}
			}
		}
	}
	while (ft_order_b(data->ar_b, data->size_b) == 0)
		{
			// if (data->ar_a[0] < data->size_b)
			// 	ft_push_b(data);
			if (data->ar_b[0] < data->ar_b[1])
				ft_swap_b(data->ar_b);
			else if (data->ar_b[0] < data->ar_b[data->size_b - 1])
				ft_rotate_b(data);
			else
		 		ft_rev_rotate_b(data);
		}
		while (data->size_b > 0)
			ft_push_a(data);
}

void	ft_resolve(t_struct *data)
{
	data->max_size = data->size_a;
	data->ar_b = (int *) malloc (sizeof(int) * data->max_size);
	data->size_b = 0;
	if(ft_order_a(data->ar_a, data->size_a) == 0)
	{
		//ft_findcomb(data);
		//printf("\n");
		//ft_printarray(data->best, data->size_best);
		//ft_sep(data);
		ft_brainfuck(data);
	}
}

int	*ft_trasformer(int *ar, int size)
{
	int	*temp;
	int *new;
	int	i;
	int	j;

	new = ft_ardup(ar, size);
	temp = (int *) malloc (sizeof(int) * size);
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

int main(int argc, char *argv[])
{
	t_struct data;

    if (argc < 2)
        ft_error();
    if (ft_check(argv, argc) == 0)
        ft_error();
	data.ar_a = ft_initializer(argv, argc);
	data.size_a = argc - 1;
	if (ft_checkfordoubles(data.ar_a, data.size_a) == 0)
		ft_error();
	data.ar_a = ft_trasformer(data.ar_a, data.size_a);
	ft_resolve(&data);
	//ft_printarray(data.ar_a, data.size_a);
	free(data.ar_a);
	free(data.ar_b);
	return (0);
}
