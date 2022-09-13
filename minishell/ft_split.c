/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:38 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 12:11:38 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_str(const char *s)
{
	int	i;
	int	flag;

	i = 0;
	if (s[i] == 34 || s[i] == 39)
	{
		if (s[i] == 34)
			flag = 34;
		else
			flag = 39;
		i++;
		while (s[i])
		{
			if (s[i] == flag)
				return (i + 1);
			i++;
		}
	}
	return (0);
}

int	ft_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && !(s[i] == c))
	{
		if (quote_str(s + i) > 0)
			return (i + quote_str(s + i));
		i++;
	}
	return (i);
}

int	ft_find_size(const char *s, char c)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (*s)
	{
		i = quote_str(s);
		if (i)
			x++;
		s += i;
		if (*s == c)
			s++;
		i = ft_len(s, c);
		if (i)
			x++;
		s += i;
		i = ft_len(s, c);
		s += i;
		if (i)
			x++;
	}
	return (x);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		x;
	char	**dst;
	int		size;

	i = 0;
	x = -1;
	if (s == NULL)
		return (NULL);
	size = ft_find_size(s, c);
	dst = malloc((size + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	while (++x < size)
	{
		while (*s == c)
			s++;
		i = quote_str(s);
		if (i != 0)
			dst[x] = ft_malloc_strcpy(s, i);
		else
		{
			i = ft_len(s, c);
			if (s[i] == 34 || s[i] == 39)
				i += quote_str(s + i);
			dst[x] = ft_malloc_strcpy(s, i);
		}
		s += i;
	}
	dst[size] = 0;
	return (dst);
}

// char	*ft_split_aux(int *i, char const *s, char c)
// {
// 	*i = ft_len(s, c);
// 	if (s[*i] == 34 || s[*i] == 39)
// 		*i += quote_str(s + *i);
// 	return (ft_malloc_strcpy(s, *i));
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	int		x;
// 	char	**dst;
// 	int		size;

// 	i = 0;
// 	x = -1;
// 	if (s == NULL)
// 		return (NULL);
// 	size = ft_find_size(s, c);
// 	dst = malloc((size + 1) * sizeof(char *));
// 	if (!dst)
// 		return (NULL);
// 	while (++x < size)
// 	{
// 		while (*s == c)
// 			s++;
// 		i = quote_str(s);
// 		if (i != 0)
// 			dst[x] = ft_malloc_strcpy(s, i);
// 		else
// 			dst[x] = ft_split_aux(&i, s, c);
// 		s += i;
// 	}
// 	dst[size] = 0;
// 	return (dst);
// }
