#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -255;
	char c = 'c';
	char *s = "str";

    printf("%-70.50u A\n", x);
	ft_printf("%-70.50u A\n", x);
    return 0;
}