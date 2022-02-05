#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -255;
	char c = 'c';
	char *s = "str";

    printf("%-30p A\n", s);
	ft_printf("%-30p A\n", s);
    return 0;
}