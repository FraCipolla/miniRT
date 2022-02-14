/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 14:27:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/02/14 15:11:39 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"	

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
		if (tab == NULL)
			return (NULL);
		while (buff[++i])
			tab[i] = buff[i];
		tab[i] = '\0';
		free(s);
		return (tab);
	}
	tab = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(buff) + 1));
	if (tab == NULL)
		return (NULL);
	while (s[++i])
		tab[i] = s[i];
	while (buff[c])
		tab[i++] = buff[c++];
	tab[i] = '\0';
	free(s);
	return (tab);
}

int	ft_strchr(const char *s, char c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == c)
			break ;
		s++;
	}
	if (*s != c)
		return (0);
	return (1);
}

void	ft_strcpy2(char *save, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] != '\0')
	{
		save[j] = str[i + j];
		j++;
	}
	str[i] = '\0';
	save[j] = '\0';
}

char	*ft_save(char *ret)
{
	char	*save;
	int		i;
	int		j;

	i = 0;
	if (ft_strchr(ret, '\n') == 0)
		return (NULL);
	while (ret[i] != '\n')
		i++;
	i += 1;
	j = i;
	while (ret[j] != '\0')
		j++;
	if (j == i)
		return (NULL);
	save = (char *) malloc (sizeof(char) * (j + 1));
	if (save == NULL)
		return (NULL);
	ft_strcpy2(save, ret, i);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*buff;
	int			tab;
	static char	*s[257];
	char		*ret;
	
	ret = s[fd];
	if (fd < 0 || fd > 256)
		return (NULL);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	tab = 1;
	while (tab > 0)
	{
		tab = read (fd, buff, BUFFER_SIZE);
		buff[tab] = '\0';
		if(tab <= 0)
			break;
		if (tab < BUFFER_SIZE)
			tab = 0;
		ret = ft_strjoin(ret, buff);
	}
	free(buff);
	s[fd] = ft_save(ret);
	return (ret);
}