#include <stdio.h>
#include "ft_printf.h"

int main()
{
	int x = 7;
	char c = 'c';
	char *s = "str";

    printf("%-7.2s A\n", s);
	ft_printf("%-7.2s A\n", s);
    return 0;
}