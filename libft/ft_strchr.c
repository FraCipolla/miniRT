#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char i;
	int x;
	char *str;

	i = (char)c;
	x = 0;
	str = (char*)s;
	if (i == '\0')
		return (&str[ft_strlen(str)]);
	while (str[x])
	{
		if (str[x] == i)
		return (&str[x]);
		x++;
	}
	return (NULL);
}