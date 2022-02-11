/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 13:49:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/11 11:30:15 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	c;

	c = 0;
	if (!s)
		return (0);
	while (s[c])
		c++;
	return (c);
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
		tab = malloc(sizeof(char) * (ft_strlen(buff) + 1));
		while (buff[++i])
			tab[i] = buff[i];
		tab[i] = '\0';
		return (tab);
	}
	tab = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(buff) + 1));
	while (s[++i])
		tab[i] = s[i];
	while (buff[c])
		tab[i++] = buff[c++];
	tab[i] = '\0';
	/*free(s);
	s = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (tab[i])
	{
		s[i] = tab[i];
		i++;
	}
	s[i] = '\0';
	if (s[0] == '\0')
		s = NULL;
	free(tab);*/
	free(s);
	return (tab);
}

char	*ft_strcat(char *s2)
{
	char	*tmp;
	int		c;
	int		i;

	c = 0;
	i = 0;
	while (s2[c] != '\n' && s2[c] != '\0')
		c++;
	if (!s2[c])
	{
		//free(s2);
		return (NULL);
	}
	if (s2[c] == '\n')
		c++;
	while (s2[i] != '\0')
		i++;
	tmp = malloc(sizeof(char) * i - c + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (s2[c] != '\0')
		tmp[i++] = s2[c++];
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_find_ret(char *s2)
{
	char	*ret;
	int		c;

	c = 0;
	if (!s2[c])
		return (NULL);
	while (s2[c - 1] != '\n' && s2[c] != '\0')
		c++;
	if (c == 0)
		c = 1;
	ret = malloc(sizeof(char) * c + 1);
	c = 0;
	while (s2[c - 1] != '\n' && s2[c] != '\0')
	{
		ret[c] = s2[c];
		c++;
	}
	ret[c] = '\0';
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			tab;
	static char	*s[257];
	char		*ret;
	
	if (fd < 0 || fd > 257)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	buff[BUFFER_SIZE] = '\0';
	tab = read (fd, buff, BUFFER_SIZE);
	if (tab <= 0 && s[fd] == NULL)
	{
		free(buff);
		return (NULL);
	}
	while (tab != 0)
	{
		s[fd] = ft_strjoin(s[fd], buff);
		tab = read (fd, buff, BUFFER_SIZE);
	}
	free(buff);
	ret = ft_find_ret(s[fd]);
	s[fd] = ft_strcat(s[fd]);	
	return (ret);
}