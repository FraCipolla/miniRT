#include "ft_libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t		n;
	char		*str;

	n = 0;
	str = (char *)b;
	while (n < len)
	{
		str[n] = (unsigned char)c;
		n++;

	}
	return (b);
}