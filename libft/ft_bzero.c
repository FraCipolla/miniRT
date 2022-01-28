#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char *dest;
	size_t			i;

	i = 0;
	dest = s;
	while (i++ < n)
		*dest++ = 0;
}