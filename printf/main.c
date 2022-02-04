#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = 7;
	char c = 'c';
	char *s = "str";

    printf("%.4d\n", x);
	ft_printf("%.4d\n", x);
    return 0;
}