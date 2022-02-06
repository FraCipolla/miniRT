#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	int x = 255;
	char c = 'c';
	char *s = "str";

    printf("%d\n", printf(" %#x ", 0));
	printf("%d\n", ft_printf(" %#x ", 0));
    return 0;
}