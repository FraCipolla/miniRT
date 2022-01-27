char	*ft_strrchr(const char *s, int c)
{
	char	r;
	int		i;

	i = 0;
	r = (char)c;
	while (s[i])
	i++;
	while (i >= 0)
	{
		if (s[i] == r)
		return (s[i])
		i--;
	}
	return (NULL);	
}