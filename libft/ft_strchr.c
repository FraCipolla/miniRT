#include "ft_libft.h"

char	*ft_strchr(const char *s, int c)
{
	char i;
	int x;

	i = (char)c;
	x = 0;
	while (s[x])
	{
		if (s[x] == c)
		return (s[x]);
		x++;
	}
	return (NULL);
}