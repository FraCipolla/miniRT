#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_putchar(char c){
	write (1, &c, 1);
	return (1);
}

int print_d(int d){
	int ret = 0;
	char str[9999];
	int i = 0;

	if (d < 0){
		ret += ft_putchar('-');
		d *= -1;
	}
	if (d == 0)
		return (ft_putchar(0 + '0'));
	while (d > 0){
		str[i] = d % 10 + '0';
		d = d / 10;
		i++;
	}
	while (str[--i]){
		ret += ft_putchar(str[i]);
	}
	return (ret);
}

int print_x(unsigned int x){
	int ret = 0;
	char str[9999];
	char *tmp = "0123456789abcdef";
	int i = 0;

	if (x == 0)
		return (ft_putchar('0'));
	while (x > 0){
		str[i] = tmp[x % 16];
		x = x / 16;
		i++;
	}
	while (str[--i])
		ret += ft_putchar(str[i]);
	return (ret);
}

int print_s(char *str){
	int ret = 0;
	int i = 0;

	while (str[i]){
		ret += ft_putchar(str[i]);
		i++;
	}
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	int	ret = 0;
	va_list args;
	int i = 0;

	va_start(args, str);
	while (str[i]){
		if (str[i] == '%'){
			i++;
			if (str[i] == 'd'){
				ret += print_d(va_arg(args, int));
				i++;
			}
			else if (str[i] == 's'){
				ret += print_s(va_arg(args, char *));
				i++;
			}
			else if (str[i] == 'x'){
				ret += print_x(va_arg(args, unsigned int));
				i++;
			}
		}
		else{
			ret += ft_putchar(str[i]);
			i++;
		}
	}
	// va_end(args);
	return (ret);
}

int main(){
	int len = ft_printf("ftPrintf: ciao %s prova %d  cioao %d dsf %d fds %d fds %d fds %x %x %x %x %x\n", "ciao", 10, 0 , -10,  -2147483648, 2147483647, -16, 0, 16, 2147483647,  -2147483648);
	int len2 =   printf("Printf:   ciao %s prova %d  cioao %d dsf %d fds %d fds %d fds %x %x %x %x %x\n", "ciao", 10, 0 , -10,  -2147483648, 2147483647, -16, 0, 16, 2147483647,  -2147483648);
	printf("%d - %d\n", len, len2);
}