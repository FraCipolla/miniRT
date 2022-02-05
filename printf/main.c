#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = -255;
	char c = 'c';
	char *s = "str";

    printf("%-20.2s A\n", s);
	ft_printf("%-20s A\n", s);
    return 0;
}