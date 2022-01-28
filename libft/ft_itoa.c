#include <stdlib.h>

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

void	put_nbr(char *tab, int n, int size)
{
	if (n > 9)
	    put_nbr (tab, n / 10, size -1);
	tab[size] = (n % 10 + '0');
}

char	*ft_itoa(int n)
{
	int		i;
	int		size;
	char	*tab;
	long int    nbr;

    nbr = (long int)n;
	i = 0;
	if (nbr < 0)
		size = find_size(nbr) + 1;
	else
		size = find_size(nbr);
	tab = malloc(sizeof(char) * size + 1);
	if (!tab)
		return (NULL);
	tab[size] = '\0';
	if (nbr < 0)
	{
		tab[0] = '-';
		nbr *= -1;
	}
	put_nbr(tab, nbr, size -1);
	return (tab);
}