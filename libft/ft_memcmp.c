#include "ft_libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*conv_s1;
	unsigned char	*conv_s2;

	i = 0;
	if (ft_strlen(conv_s1) == 0 && ft_strlen(conv_s2) == 0)
		return (0);
	while (i < n && s1[i] == s2[i])
	{
		if (conv_s1[i] != conv_s2[i])
		return (conv_s1[i] - conv_s2[i]);
		i++;
	}
	return (0);
}