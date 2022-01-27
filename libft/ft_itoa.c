#include <stlib.h>
#include <unistd.h>

int	find_size(int n)
{
	int	c;

	c = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		n /= 10;
		c++;
	}
	return (c);
}

char	put_nbr(char *tab, int n)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (n < 0)
			tab[i] = '-';
		if (n <= 9)
			tab[i] = n + '0';
		if (n > 9)
		{
			put_nbr (tab, n / 10)
			put_nbr (tab, n % 10)
		}
	i++;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	int		size;
	char	*tab;

	i = 0;
	if (n < 0)
		size = find_size(n) + 1;
	else
		size = find_size(n);
	tab = malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	
}