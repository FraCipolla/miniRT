#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	int x = 255;
	char c = 'c';
	char *s = "str";

    printf("%d\n", printf(" %d ", ULONG_MAX));
	printf("%d\n", ft_printf(" %d ", ULONG_MAX));
    return 0;
}