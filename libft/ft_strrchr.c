#include "ft_libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	r;
	int		i;
	char	*str;

	i = 0;
	r = (char)c;
	str = (char*)s;
	while (str[i])
	i++;
	while (i >= 0)
	{
		if (str[i] == r)
		return (&str[i]);
		i--;
	}
	return (NULL);	
}