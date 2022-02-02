/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 19:45:35 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/02 13:00:13 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putchar(char c, t_list *params)
{
		write (1, &c, 1);
		params->ret += 1;

}

void	ft_print_args (va_list args, t_list *params)
{
	if (params->di == 1)
		ft_print_di(va_arg(args, unsigned int), &params);
	if (params->u == 1)
	{
		params->plus = 0;
		ft_print_di(va_arg(args, long int), &params);
	}
	if (params->x == 1)
		ft_print_x(va_arg(args, unsigned int), &params);
	if (params->X == 1)
		ft_print_X(va_arg(args, unsigned int), &params);
	if (params->s == 1)
		ft_print_s(va_arg(args, char *), &params);
	if (params->c == 1)
		ft_print_c(va_arg(args, int), &params);
	if (params->p == 1)
		ft_print_p(va_arg(args, long unsigned int), &params);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char	*tmp;
	char	*tab;
	int		i;
	int		c;
	t_list params;

	va_start (args, format);
	i = 0;
	while (format[i])
	{
		if (format[i - 1] == '%')
		{
			c = 0;
			while (format[i] != '\0' || format[i + 1] != '%')
			{
				if (ft_check_type(format[i], &params));
					break;
				tmp[c++] = format[i++];
			}
			tab = malloc(sizeof(char) * c + 1;
			tab[c + 1] = '\0';
			ft_check_params(tmp, &params);
			ft_print_args (args, &params);
			free(tab);
		}
		else
			ft_putchar (format[i]);
		i++;
	}
	va_end (args);
	return (params.ret);
}