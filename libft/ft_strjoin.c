#include <stlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{	
	char *tab;
	int		i;
	int		c;

	i = 0;
	tab = (char)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!tab)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++
	}
	while (s2[c])
	{
		tab[i] = s2[c];
		i++;
		c++;
	}
	return (tab);
}