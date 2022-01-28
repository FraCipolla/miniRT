void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	whilt (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}