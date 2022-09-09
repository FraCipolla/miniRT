/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 13:24:40 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/05 18:00:16 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			n++;
	}
	ret = malloc(sizeof(char *) * i - (n * 2) + 1);
	i = -1;
	n = 0;
	while (args[++i])
	{
		if (strcmp(args[i], ">>") == 0 || args[i][0] == '>' || args[i][0] == '<' || strcmp(args[i], "<<") == 0)
			i++;
		else
		{
			ret[n] = ft_strdup(args[i]);
			n++;
		}
	}
	ret[n] = NULL;
	return (ret);
}

int	check_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 33 && str[i] <= 126)
			return (0);
		i++;
	}
	return (-1);
}

char	*ft_strjoin2(char *s1, char *s2, int q)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL)
		size = ft_strlen(s2);
	else
		size = ft_strlen(s1) + ft_strlen(s2);
	if (size == 0)
		return (NULL);
	str = (char *) malloc (sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (s1 != NULL)
		i += ft_strcpy(str, s1);
	j = -1;
	while (s2[++j] != '\0')
	{
		if (q != 0 && s2[j] != q)
		{
			str[i] = s2[j];
			i++;
		}
		else if (s2[j] != '"' && s2[j] != '\'')
		{
			str[i] = s2[j];
			i++;
		}
	}
	return (str);
}

char	*str_to_print(char **str2, char *str)
{
	char	*ret;
	int		i;
	char	**tmp;
	int		q;

	i = 0;
	ret = NULL;
	tmp = ft_split(str, '\n');
	q = 0;
	while (strncmp(str2[i], "echo", 4) != 0)
		i++;
	if (strcmp(str2[i + 1], "-n") == 0)
		i++;
	i++;
	while (str2[i])
	{
		ret = ft_strjoin2(ret, str2[i], q);
		ret = ft_strjoin(ret, " ");
		i++;
	}
	return (ret);
}

int	my_echo(char **args, char *str)
{
	char	*cmd;
	int		i;

	// if (check_redir(args) == -1)
	// 	exit (0);
	i = -1;
	// while (args[++i])
	// 	printf("%s\n", args[i]);
	args = cut_red(args);
	// printf("STR: %s\n", str);
	i = 0;
	cmd = str_to_print(args, str);
	while (args[++i])
		if (strcmp(args[i], "-n") == 0)
			cmd[ft_strlen(cmd) - 1] = '%';
	printf("%s\n", cmd);
	exit (0);
}