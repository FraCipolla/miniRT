#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -255;
	char c = 'c';
	char *s = "str";

    printf("%u A\n", x);
	ft_printf("%u A\n", x);
    return 0;
}