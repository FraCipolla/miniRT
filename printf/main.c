#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int d = 5;
	char c = 'c';
	char *s = "str";

    printf("%d\n", d);
	ft_printf("%d", d);
    return 0;
}