int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;
	int	a;

	i = 0;
	j = 0;
	a = ft_strlen(needle);
	if (a == 0)
		return (haystack);
	while (haystack[i] != '\0')
	{
		while (haystack[i] != needle[j] && haystack[i] != '\0' && i < len)
			i++;
		while (haystack[i] == needle[j] && haystack[i] != '\0' && i < len)
		{
			i++;
			j++;
		}
		if (j == a)
			return (haystack + i - j);
		else
			j = 0;
	}
	return (0);
}