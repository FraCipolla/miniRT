/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 17:35:38 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/24 23:59:58 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_str(const char *s)
{
	int	i;
	int	flag;
	int	par;

	i = -1;
	par = 0;
	while (s[++i])
		if (s[i] == '(')
			par++;
	i = 0;
	if (s[i] == 34 || s[i] == 39 || s[i] == '(')
	{
		if (s[i] == 34)
			flag = 34;
		else if (s[i] == 39)
			flag = 39;
		else
			flag = ')';
		i++;
		while (s[i])
		{
			if (flag == ')' && s[i] == flag)
			{
				par--;
				if (par == 0)
					return (i + 1);
			}
			else if (flag != ')' && s[i] == flag)
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
	while (s[i] && s[i] != c)
	{
		if (quote_str(s + i) > 0)
			i += quote_str(s + i);
		else
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
		i = ft_len(s, c);
		if (i)
			x++;
		s += i;
		if (*s == c)
			s++;
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
		i = ft_len(s, c);
		if (i != 0)
			dst[x] = ft_malloc_strcpy(s, i);
		// printf("split: %d %s\n", i, dst[x]);
		s += i;
	}
	dst[size] = 0;
	// printf("dst[0]: %s\n", dst[0]);
	return (dst);
}
