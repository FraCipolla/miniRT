/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:42:19 by mcipolla          #+#    #+#             */
/*   Updated: 2022/03/16 04:22:22 by mcipolla         ###   ########.fr       */
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

void	ft_combine_ab(t_struct *data)
{
	int	i;

	i = 0;
	while (data->size_b > 0)
		ft_push_a(data);
}

int	ft_check_arr_b(t_struct *data)
{
	int	i;

	i = 0;
	if (data->size_b == 1)
		return (0);
	while (data->size_b > i) 
	{
		if (data->ar_b[i] < data->ar_b[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_arr_a(t_struct *data)
{
	int	i;

	i = 0;
	if (data->size_a == 1)
		return (0);
	while (i < data->size_a)
	{
		if (data->ar_a[i] > data->ar_a[i + 1])
			return (1);
		i++;
	}
	return (0);
}

void	ft_brainfuck(t_struct *data)
{
	int	size;

	if (data->max_size == 3)
		size = 1;
	else
		size = data->max_size / 2 - 1;
	while (data->size_b < size)
	{
		if (data->ar_a[0] <= data->max_size / 2)
			ft_push_b(data);
		else
			ft_rotate_a(data);
	}
	while (ft_check_arr_a(data) == 1 || ft_check_arr_b(data) == 1)
	{
		if (data->ar_a[0] > data->ar_a[1] && ft_check_arr_a(data) == 1)
		{
			if (data->ar_b[0] < data->ar_b[1] && ft_check_arr_b(data) == 1)
				ft_swap_s(data->ar_a, data->ar_b);
			else
				ft_swap_a(data->ar_a);
		}
		else if (data->ar_a[0] > data->ar_a[data->size_a - 1] && ft_check_arr_a(data) == 1)
		{
			if (data->ar_b[0] < data->ar_b[data->size_b - 1] && ft_check_arr_b(data) == 1)
				ft_rev_rotate_r(data);
			else
				ft_rev_rotate_a(data);
		}
		else if (data->ar_a[0] < data->ar_a[data->size_a - 1] && ft_check_arr_a(data) == 1)
		{
			if (data->ar_b[0] > data->ar_b[data->size_b - 1] && ft_check_arr_b(data) == 1)
				ft_rotate_r(data);
			else
				ft_rotate_a(data);
		}
	}
	printf("ENTRA");
	ft_combine_ab(data);
}

void	ft_resolve(t_struct *data)
{
	data->max_size = data->size_a;
	data->ar_b = (int *) malloc (sizeof(int) * data->max_size);
	data->size_b = 0;
	if(ft_order(data->ar_a, data->size_a) == 0)
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
