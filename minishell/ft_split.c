/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:38 by mcipolla          #+#    #+#             */
/*   Updated: 2022/06/23 15:28:26 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_sep(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

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
	while (s[i] && ft_sep(s[i], c) == 0)
	{
		if (quote_str(s + i) > 0)
			return (i);
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
		if (ft_sep (*s, c) == 1)
			s++;
		i = quote_str(s);
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

char	*ft_malloc_strcpy(const char *s, int n)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc((n + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (i < n && s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		x;
	char	**dst;
	int		size;

	i = 0;
	x = 0;
	if (s == NULL)
		return (NULL);
	size = ft_find_size(s, c);
	dst = malloc((size + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	while (x < size)
	{
		while (ft_sep(*s, c))
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
		x++;
	}
	dst[size] = 0;
	return (dst);
}
