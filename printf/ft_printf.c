/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/04 14:34:24 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_print_args(va_list args, t_list *params)
{
	/*printf("ARG: %d\n", params->di);
	printf("ARG: %d\n", params->u);
	printf("ARG: %d\n", params->x);
	printf("ARG: %d\n", params->X);
	printf("ARG: %d\n", params->s);
	printf("ARG: %d\n", params->c);
	printf("ARG: %d\n", params->p);
	printf("ARG: %d\n", params->plus);*/
	if (params->di == 1)
		ft_print_di(va_arg(args, int), params);
	else if (params->u == 1)
	{
		params->plus = 0;
		ft_print_di(va_arg(args, int), params);
	}
	else if (params->x == 1 || params->X == 1)
		ft_print_hex(va_arg(args, unsigned int), params);
	else if (params->s == 1)
		ft_print_s(va_arg(args, char *), params);
	else if (params->c == 1)
		ft_print_c(va_arg(args, int), params);
	else if (params->p == 1)
		ft_print_p(va_arg(args, long unsigned int), params);
	//printf("END_ARGS\n");
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*tmp;
	char	*tab;
	int		i;
	int		c;
	int		m;
	t_list params;

	va_start (args, format);
	ft_utility(&params);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			c = 0;
			while (ft_check_type (format[i], &params) == 0)
				tmp[c++] = format[i++];
			tab = malloc(sizeof(char) * c + 1);
			m = -1;
			while (++m < c)
				tab[m] = tmp[m];
			tab[c] = '\0';
			//ft_check_type(format[i], &params);
			ft_check_params(tab, &params);
			ft_print_args(args, &params);
			free(tab);
		}
		else
			ft_putchar (format[i], &params);
		i++;
	}
	va_end (args);
	return (params.ret);
}