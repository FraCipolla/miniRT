#include "ft_libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
	i++;
	while (dst[i] && src[j] && j < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (dstsize < dst)
	dst[dstsize] = '\0';
	return (dst);
}