/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/07 14:30:37 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// char	**cut_red(char **args)
// {
// 	int		i;
// 	int		n;
// 	char	**ret;

// 	i = -1;
// 	n = 0;
// 	while (args[++i])
// 	{
// 		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>'
// 			|| args[i][0] == '<' || strcmp(args[i], "<<") == 0)
// 			n++;
// 	}
// 	ret = malloc(sizeof(char *) * i - (n * 2) + 1);
// 	i = -1;
// 	n = 0;
// 	while (args[++i])
// 	{
// 		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>'
// 			|| args[i][0] == '<' || strcmp(args[i], "<<") == 0)
// 			i++;
// 		else
// 			ret[n++] = ft_strdup(args[i]);
// 	}
// 	ret[n] = NULL;
// 	return (ret);
// }
char	**cut_red(char **args, int n)
{
	int		i;
	char	**ret;

	i = -1;
	while (args[++i])
	{
		if (memcmp_aux(i, args))
			n += 2;
		else if (args[i][0] == '>' || args[i][0] == '<')
			n++;
	}
	ret = ft_calloc(i - n + 1, sizeof(char *));
	i = 0;
	n = 0;
	while (args[i])
	{
		if (memcmp_aux(i, args))
			i += 2;
		else if (args[i][0] == '>' || args[i][0] == '<')
			i++;
		else
			ret[n++] = ft_strdup(args[i++]);
	}
	return (ret);
}

char	**cut_echo(char **args)
{
	int		i;
	char	**ret;
	int		c;

	i = 0;
	c = 0;
	while (args[i])
		i++;
	ret = malloc((i +1) * sizeof(char *));
	ret[i] = 0;
	i = -1;
	while (args[++i])
	{
		if (!strcmp(args[i], "echo"))
			break ;
	}
	while (args[++i])
	{
		if (args[i][0] == '>')
			break ;
		ret[c] = strdup(args[i]);
		c++;
	}
	ret[c] = 0;
	return (ret);
}

char	*manage_env(char *str)
{
	char	*aux;
	char	*aux1;
	int		i;

	i = 0;
	if (*(str) == '?')
	{
		write(1, "bho", 3);
		return (str + 1);
	}
	while (str[i] && str[i] != ' ' && str[i]
		!= '"' && str[i] != '\'' && str[i] != '$')
		i++;
	aux = ft_calloc(i, 1);
	i = -1;
	while (str[++i] && str[i] != ' ' && str[i]
		!= '"' && str[i] != '\'' && str[i] != '$')
		aux[i] = str[i];
	if (!*aux)
		return ("$");
	aux1 = getenv(aux);
	if (aux1 == NULL)
		return (NULL);
	return (aux1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

int	my_echo(char **args, char *str, int fd)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	str = NULL;
	args = cut_echo(args);
	while (strcmp(args[i], "-n") == 0)
		i++;
	if (i > 0)
		flag = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		write(1, " ", 1);
		i++;
		if (args[i] == NULL)
			break ;
	}
	if (flag == 0)
		write(fd, "\n", 1);
	exit (0);
}
