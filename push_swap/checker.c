/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:22:19 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/11 17:22:19 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_checkmove(char *str)
{
	if (ft_strcmp(str, "pa\n") == 0)
		return ;
	if (ft_strcmp(str, "pb\n") == 0)
		return ;
	if (ft_strcmp(str, "ra\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		return ;
	if (ft_strcmp(str, "rb\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		return ;
	if (ft_strcmp(str, "rra\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		return ;
	if (ft_strcmp(str, "rrb\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		return ;
	if (ft_strcmp(str, "sa\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		return ;
	if (ft_strcmp(str, "sb\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		return ;
	ft_error();
}

void	ft_correct(t_struct *data, char *str)
{
	ft_checkmove(str);
	if (ft_strcmp(str, "pa\n") == 0)
		ft_push(data->ar_b, data->ar_a, &data->size_b, &data->size_a);
	if (ft_strcmp(str, "pb\n") == 0)
		ft_push(data->ar_a, data->ar_b, &data->size_a, &data->size_b);
	if (ft_strcmp(str, "ra\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		ft_rotate(data->ar_a, data->size_a);
	if (ft_strcmp(str, "rb\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		ft_rotate(data->ar_b, data->size_b);
	if (ft_strcmp(str, "rra\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		ft_rev_rotate(data->ar_a, data->size_a);
	if (ft_strcmp(str, "rrb\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		ft_rev_rotate(data->ar_b, data->size_b);
	if (ft_strcmp(str, "sa\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		ft_swap(data->ar_a, data->ar_a + 1, data->size_a);
	if (ft_strcmp(str, "sb\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		ft_swap(data->ar_b, data->ar_b + 1, data->size_b);
}

void	ft_control(t_struct *data)
{
	char	*str;

	str = get_next_line(0);
	while (ft_order(data->ar_a, data->size_a) == 0 || data->size_b != 0)
	{
		if (str == NULL)
			break ;
		ft_correct(data, str);
		free (str);
		str = get_next_line(0);
	}
	if (str != NULL)
		free(str);
	if (ft_order(data->ar_a, data->size_a) == 1)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
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
	data.ar_b = (int *) malloc (sizeof(int) * data.size_a);
	data.size_b = 0;
	ft_control(&data);
	free(data.ar_a);
	free(data.ar_b);
	return (0);
}
