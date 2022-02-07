/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:49:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/07 19:25:21 by mcipolla         ###   ########.fr       */
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
	while (s[c - 1] != '\n' && s[c])
		c++;
	tmp = malloc(sizeof(char) * (ft_strlen(s) - c + 1));
	while (s[c])
		tmp[i++] = s[c++];
	tmp[i] = '\0';
	free(s);
	s = malloc(sizeof(char) * (i + 1));
	c = 0;
	while (tmp[c])
	{
		s[c] = tmp [c];
		c++;
	}
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
	//printf("LEN: %d\n", ft_strlen(s) + ft_strlen(buff) + 1);
	//printf("S: %s\n", s);
	while (s[++i])
		tab[i] = s[i];
	//printf("TAB: %s\n", tab);
	while (buff[c])
	{
		tab[i] = buff[c];
		i++;
		c++;
	}
	tab[i] = '\0';
	free(s);
	s = malloc(sizeof(char) * (i + 1));
	//printf("BUFF: %s\n", buff);
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
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	tab = read (fd, buff, BUFFER_SIZE);
	buff[tab] = '\0';
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
	while (s[c] && s[c - 1] != '\n')
		c++;
	ret = malloc(sizeof(char) * c + 1);
	ret[c] = '\0';
	c = 0;
	while (ret[c])
	{
		ret[c] = s[c];
		c++;
	}
	s = ft_strcat(s);
	free(buff);
	free(s);
	return (ret);
}