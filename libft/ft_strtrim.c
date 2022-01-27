int	check_set(char c, char const *set, int i)
{
	if (set[i] == c)
		return (1);
	else
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
	len = ft_strlen(s1);
	while (check_set(s1[i], set, i) == 1)
		i++;
	while (check_set(s1[len], set, len) == 1)
		len--;
	size = len - i;
	tab = (char)malloc(sizeof(char) * size);
	if (!tab)
		return(NULL);
	c = 0;
	while (i < len)
	{
		tab[c] = s1[i];
		c++;
		i++;
	}
	return (tab);
}