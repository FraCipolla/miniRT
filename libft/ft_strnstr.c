#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = ft_strlen(needle);
	if (a == 0)
		return ((char*)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		while (haystack[i] != needle[j] && haystack[i] != '\0' && i < len)
			i++;
		while (haystack[i] == needle[j] && haystack[i] != '\0' && i < len)
		{
			i++;
			j++;
		}
		if (j == a)
			return ((char*)haystack + i - j);
		else
			j = 0;
	}
	return (0);
}