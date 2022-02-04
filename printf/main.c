#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = 7;
	char c = 'c';
	char *s = "str";

    printf("%7.4d\n", x);
	ft_printf("%7.4d\n", x);
    return 0;
}