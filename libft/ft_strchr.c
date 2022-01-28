#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char i;
	int x;
	char *str;

	i = (char)c;
	x = 0;
	str = (char*)s;
	while (str[x])
	{
		if (str[x] == c)
		return (&str[x]);
		x++;
	}
	return (NULL);
}