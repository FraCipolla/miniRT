#include <stlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char const		*tab;
	unsigned int	i;

	i = 0;
	tab = (char)malloc(sizeof(char) * len));
	if (!tab)
		return(NULL);
	while(i <= len)
	{
		tab[i] = s[start];
		i++;
		start++;
	}
	return (tab);
}