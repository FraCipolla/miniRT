#include <stdio.h>
#include "ft_printf.h"


int main()
{
	printf("%d\n", printf("%0014.2X%020X%0002.X%000.5X", -1, 3, 30, -1));
	printf("%d\n", ft_printf("%0014.2X%020X%0002.X%000.5X", -1, 3, 30, -1));
	return (0);
}