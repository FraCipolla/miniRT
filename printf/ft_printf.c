void	ft_putchar_pf(char c)
{
		write (1, &c, 1);
}

void	ft_check_type (char *str, ...)
{
	int	c;

	c = 0;
	while (str[c++])
	{
		
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	char *tmp;
	int	i;
	int	c;

	va_start (args, format);
	i = 0;
	c = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			c = 0;
			while (format[i] != ' ' || format[i] != '\0' || format[i + 1] != '%')
				tmp[c++] = format[i++];
			ft_check_type(tmp, args);
		}
		else
			ft_putchar_pf (format[i]);
		i++;
	}
}