/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 19:28:12 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/21 15:40:11 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_new_size(char	*str)
{
	int		i;
	int		size;

	i = -1;
	size = 0;
	while (str[++i])
	{
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			size++;
		else if (ft_strncmp(str + i, ">>", 2) == 0 || ft_strncmp(str + i, "<<", 2) == 0)
		{
			if (str[i + 2] != ' ')
				size++;
		}
	}
	return (i + size);
}

char	*ft_addspaces(char *str)
{
	int		i;
	int		c;
	char	*ret;

	i = -1;
	c = 0;
	ret = malloc(sizeof(char) * ft_find_new_size(str) + 1);
	while (str[++i])
	{
		ret[c] = str[i];
		if ((str[i] == '>' || str[i] == '<') && str[i + 1] != ' ' && str[i + 1] != '>' && str[i + 1] != '<')
			ret[++c] = ' ';
		else if (ft_strncmp(str + i, ">>", 2) == 0 || ft_strncmp(str + i, "<<", 2) == 0)
		{
			if (str[i + 2] == '<' || str[i + 2] == '>')
			{
				printf("bash: syntax error near unexpected token '%c'\n", str[i + 2]);
				free(ret);
				free(str);
				return (NULL);
			}
			else if (str[i + 2] != ' ')
			{
				ret[++c] = str[++i];
				ret[++c] = ' ';
			}
		}
		c++;
	}
	ret[c] = '\0';
	free(str);
	return (ret);
}

char	**cut_red(char **args)
{
	int		i;
	int		n;
	char	**ret;

	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
			n += 2;
	}
	ret = malloc(sizeof(char *) * i - (n) + 1);
	i = 0;
	n = 0;
	while (args[i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
			i += 2;
		else
		{
			ret[n] = ft_strdup(args[i]);
			n++;
			i++;
		}
	}
	ret[n] = NULL;
	return (ret);
}

// int	memcmp_aux(int i, char **args)
// {
// 	if (!memcmp(args[i], ">\0", 2) || !memcmp(args[i], ">>\0", 3)
// 		|| !memcmp(args[i], "<\0", 2) || !memcmp(args[i], "<<\0", 3))
// 		return (1);
// 	return (0);
// }

// int	cut_red_aux(char **args)
// {
// 	int	i;
// 	int	n;

// 	i = -1;
// 	n = 0;
// 	while (args[++i])
// 	{
// 		if (memcmp_aux(i, args))
// 			n += 2;
// 		else if (args[i][0] == '>' || args[i][0] == '<')
// 			n++;
// 	}
// 	return (n);
// }

// int	check_redir_aux1(char **args, int i)
// {
// 	int	fd;

// 	fd = 1;
// 	if (memcmp(args[i], ">\0", 2) == 0 || memcmp(args[i], ">>\0", 3) == 0)
// 	{
// 		if (memcmp(args[i], ">\0", 2) == 0)
// 			fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		else
// 			fd = open(args[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
// 		dup2(fd, 1);
// 	}
// 	else if (args[i][0] == '>')
// 	{
// 		if (!strncmp(args[i], ">>", 2))
// 			fd = open(args[i] + 2, O_CREAT | O_RDWR | O_APPEND, 0644);
// 		else
// 			fd = open(args[i] + 1, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 		dup2(fd, 1);
// 	}
// 	return (fd);
// }

// int	check_redir_aux2(char **args, int i)
// {
// 	int	fd;

// 	fd = 1;
// 	if (memcmp(args[i], "<\0", 2) == 0 || memcmp(args[i], "<<\0", 3) == 0)
// 	{
// 		if (memcmp(args[i], "<\0", 2) == 0)
// 			fd = open(args[i + 1], O_RDONLY, 0644);
// 		else
// 			here_doc(args[i + 1]);
// 		dup2(fd, 0);
// 	}
// 	else if (args[i][0] == '<')
// 	{
// 		if (!strncmp(args[i], "<<", 2))
// 			here_doc(args[i] + 2);
// 		else
// 			fd = open(args[i] + 1, O_RDONLY, 0644);
// 		dup2(fd, 1);
// 	}
// 	return (fd);
// }
