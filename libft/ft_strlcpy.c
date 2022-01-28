#include "ft_libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	while (dst[i] && src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[dstsize] = '\0';
	return (dst);
}