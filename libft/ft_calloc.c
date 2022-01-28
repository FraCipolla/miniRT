#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = malloc(count * size);
	ft_bzero(tab, count * size);
	return (tab);
}