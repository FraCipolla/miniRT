void	*ft_memset(void *b, int c, size_t len)
{
	int		n;
	char	*str;

	n = 0;
	str = (char *)b;
	while (n < len)
	{
		str[n] = (unsigned char)c;
		n++;

	}
	return (b);
}