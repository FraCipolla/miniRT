#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	int x = 255;
	char c = 'c';
	char *s = "str";

    printf("%d\n", printf(" %.2u ", -1));
	printf("%d\n", ft_printf(" %.2u ", -1));
    return 0;
}