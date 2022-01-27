#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int	i;
	char *tab;

	i = 0;
	while (s1[i])
		i++;
	tab = (char)malloc(sizeof(char) * i + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}