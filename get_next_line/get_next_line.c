/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:49:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 22:39:00 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	c;

	c = 0;
	while (s[c])
		c++;
	return (c);
}

char	*ft_strcat(char *s)
{
	char	*tmp;
	int		c;
	int		i;

	c = 0;
	i = 0;
	while (s[c - 1] != '\n' && s[c] != '\0')
		c++;
//	printf("C2: %d\n", c);
	tmp = malloc(sizeof(char) * ft_strlen(s) - c + 1);
	//printf("S: %s\n", s);
//	printf("SC: %c\n", s[c]);
//	printf("LEN: %d\n", ft_strlen(s) - c + 1);
//	printf("C2: %d\n", c);
	while (s[c] != '\0')
	{
		tmp[i] = s[c];
		i++;
		c++;
	}
	tmp[i] = '\0';
//	printf("C2: %d\n", c);
//	printf("I: %d\n", i);
//	printf("TMP: %s\n", tmp);
	free(s);
//	printf("I: %d\n", i);
	s = malloc(sizeof(char) * (i + 1));
	c = 0;
	while (tmp[c])
	{
		s[c] = tmp[c];
		c++;
	}
	s[c] = '\0';
//	printf("S: %s\n", s);
	//printf("SLEN: %d\n", ft_strlen(s));
	free(tmp);
	return (s);
}

char	*ft_strjoin(char *s, char *buff)
{
	char	*tab;
	int		i;
	int		c;

	c = 0;
	i = -1;
	if (s == NULL)
	{
		s = malloc(sizeof(char) * (ft_strlen(buff) + 1));
		while (buff[++i])
			s[i] = buff[i];
		s[i] = '\0';
		return (s);
	}
	tab = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(buff) + 1));
	while (s[++i])
		tab[i] = s[i];
	while (buff[c])
		tab[i++] = buff[c++];
	tab[i] = '\0';
	free(s);
	s = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (tab[i])
	{
		s[i] = tab[i];
		i++;
	}
	s[i] = '\0';
	free(tab);
	return (s);
}

char	*ft_find_ret(char *s)
{
	char	*ret;
	int		c;

	c = 0;
	while (s[c] != '\n' && s[c] != '\0')
		c++;
	if (c == 0)
		c = 1;
	//printf("SC: %c\n", s[c -1]);
	//printf("C: %d\n", c);
	ret = malloc(sizeof(char) * c + 1);
	ret[c] = '\0';
	c = 0;
	while (s[c] != '\n' && s[c] != '\0')
	{
		ret[c] = s[c];
		c++;
	}
	return (ret);
}
char	*get_next_line(int fd)
{
	char		*buff;
	int			tab;
	static char	*s = NULL;
	int			c;
	char		*ret;

	c = 0;
	if (fd < 0 || fd > 257)
		return (NULL);
	if (s == NULL)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (NULL);
		tab = read (fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = '\0';
		if (tab <= 0)
		{
			free(buff);
			return (NULL);
		}
		while (tab != 0)
		{
			s = ft_strjoin(s, buff);
			tab = read (fd, buff, BUFFER_SIZE);
		}
		free(buff);
	}
	ret = ft_find_ret(s);
//	printf("RET: %s\n", ret);
	s = ft_strcat(s);
	return (ret);
}