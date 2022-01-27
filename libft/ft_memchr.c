void	*memchr(const void *s, int c, size_t n)
{
	unsigned char	x;
	char 			*str;
	int				i;

	i = 0;
	str = (char *)s;
	x = (unsigned char)c;
	while (str[i] && i < n)
	{
		if (str[i] == x)
		return (str[i]);
		i++;
	}
	return (NULL);

}