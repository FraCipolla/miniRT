#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int d = 7;
	char c = 'c';
	char *s = "str";

    printf("%.5d\n", d);
	ft_printf("%.5d\n", d);
    return 0;
}