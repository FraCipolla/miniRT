void	ft_print_s(va_list args)
{
	int	len;
	int	c;

	c = 0;
	len = 0;
	while (args[len++])
	if (params -> min == 1)
	{
		if (params -> dot == 1 && params.precision < len)
		{
			while(c++ < params.precision)
				ft_putchar(args[c]);
			while (c++ < params.witdh)
				ft_putchar(' ');
		}
		else
		{
			ft_putstr(args);
			while (params.width > len++)
				ft_putchar (' ');
		}
	}
	else
		while (params.width > len++)
			ft_putchar (' ');
		ft_putstr(args);
	}		
}