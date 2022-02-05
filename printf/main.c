#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -255;
	char c = 'c';
	char *s = "str";

    printf("%#-50.30x A\n", x);
	ft_printf("%#-50.30x A\n", x);
    return 0;
}