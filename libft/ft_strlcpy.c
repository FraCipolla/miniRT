#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dst[i] && src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[dstsize] = '\0';
	return (ft_strlen(src));
}