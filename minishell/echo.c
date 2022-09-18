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
// char	**cut_red(char **args, int n)
// {
// 	int		i;
// 	char	**ret;

// 	i = -1;
// 	n = 0;
// 	while (args[++i])
// 	{
// 		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
// 			n++;
// 	}
// 	ret = malloc(sizeof(char *) * i - (n * 2) + 1);
// 	i = -1;
// 	n = 0;
// 	while (args[++i])
// 	{
// 		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
// 			i++;
// 		else
// 		{
// 			ret[n] = ft_strdup(args[i]);
// 			n++;
// 		}
// 	}
// 	ret[n] = NULL;
// 	return (ret);
// }
// char	**cut_red(char **args, int n)
// {
// 	int		i;
// 	char	**ret;

// 	i = -1;
// 	while (args[++i])
// 	{
// 		if (memcmp_aux(i, args))
// 			n += 2;
// 		else if (args[i][0] == '>' || args[i][0] == '<')
// 			n++;
// 	}
// 	ret = ft_calloc(i - n + 1, sizeof(char *));
// 	i = 0;
// 	n = 0;
// 	while (args[i])
// 	{
// 		if (memcmp_aux(i, args))
// 			i += 2;
// 		else if (args[i][0] == '>' || args[i][0] == '<')
// 			i++;
// 		else
// 			ret[n++] = ft_strdup(args[i++]);
// 	}
// 	return (ret);
// }

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
		write(1, &exit_value + '0', 3);
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
	int		i;
	char	c;

	i = 0;
	c = exit_value + '0';
	if (ft_strcmp(str, "$?") == 0)
		write (fd, &c, 1);
	else
	{
		while (str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

int	my_echo(char **args, int fd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	// printf("%s\n%s\n", args[0], args[1]);
	// args = cut_echo(args);
	while (strcmp(args[i], "-n") == 0)
	{
		i++;
		flag = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		i++;
		if (args[i] == NULL)
			break ;
		ft_putstr_fd(" ", fd);
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	return (0);
}
