#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	int x = 255;
	char c = 'c';
	char *s = "str";

    printf("%d\n", printf(" % d ", INT_MAX));
	printf("%d\n", ft_printf(" % d ", INT_MAX));
    return 0;
}