#include <stlib.h>

int	check_set(char c, char const *set)
{
	int	x;

	x = 0;
	while (set[x])
	{
		if (set[x] == c)
			return (1);
		x++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		size;
	int 	len;
	char	*tab;
	int		c;

	i = 0;
	len = ft_strlen(s1) - 1;
	while (check_set(s1[i], set) == 1)
		i++;
	if (i >= ft_strlen(s1) - 1)
		return (NULL);
	while (check_set(s1[len], set) == 1)
		len--;
	size = len - i;
	tab = (char)malloc(sizeof(char) * size + 2);
	if (!tab)
		return(NULL);
	c = 0;
	while (i <= len)
	{
		tab[c] = s1[i];
		c++;
		i++;
	}
	tab[c] = '\0';
	return (tab);
}