#include <stdio.h>
#include "ft_printf.h"
#include <limits.h>

int main()
{
	int x = 255;
	char c = 'c';
	char *s = "str";

    printf("%d\n", printf(" %04u ", 9));
	printf("%d\n", ft_printf(" %04u ", 9));
    return 0;
}