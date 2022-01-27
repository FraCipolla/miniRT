#include <stdlib>

char	*ft_strdup(const char *s1)
{
	int	i;
	char *tab;

	i = 0;
	while (s1[i])
	i++;
	tab = (char)malloc(sizeof(char) * i);
	if (!tab)
	return (NULL);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	return (tab);
}