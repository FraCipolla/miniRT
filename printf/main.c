#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = 7;
	char c = 'c';
	char *s = "str";

    printf("%.5s\n", s);
	ft_printf("%.5s\n", s);
    return 0;
}