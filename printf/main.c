#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -255;
	char c = 'c';
	char *s = "str";

    printf("%d\n", printf(" %c %c %c ", 'a', 'b', 'c'));
	printf("%d\n", ft_printf(" %c %c %c ", 'a', 'b', 'c'));
    return 0;
}