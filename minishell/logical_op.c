/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:25:42 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 15:39:01 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_emptyline(char *str)
{
	while (*str)
	{
		if (*str != ' ')
			return (1);
		str++;
	}
	return (0);
}

char	*cut_str(char *str, int limiter)
{
	char	*ret;
	int		i;

	if (str[limiter + 1] == '\0')
		limiter += 1;
	ret = malloc(sizeof(char) * limiter);
	ret[limiter] = '\0';
	i = -1;
	while (++i < limiter)
		ret[i] = str[i];
	return (ret);
}

int	exec_logical(char *buff, char **mypath, int i, char **envp)
{
	char	*tmp;
	char	**args;
	int		pid;

	tmp = cut_str(buff, i);
	args = ft_split(tmp, ' ');
	args = check_wild(args);
	pid = fork();
	if (pid == 0)
	{
		check_pipes(tmp, mypath, remove_quotes(args), envp);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
		my_free(args);
		free(tmp);
	}
	if (buff[i + 1] == '\0')
		return (1);
	return (0);
}

int	logical_operator(char *buff, char **mypath, char *log, char **envp)
{
	int		i;

	if (*buff == ' ')
		buff++;
	// printf("buff %s\n", buff);
	// i = quote_str(buff);
	// if (buff[i] == '\0')
	// 	i--;
	i = 0;
	while (buff[i])
	{
		if ((buff[i + 1] == '\0' && log != NULL)
			|| ft_strncmp(&buff[i], "&&", 2) == 0
			|| ft_strncmp(buff + i, "||", 2) == 0)
		{
			if (log == NULL
				|| (ft_strncmp(log, "&&", 2) == 0 && g_exit == 0)
				|| (ft_strncmp(log, "||", 2) == 0 && g_exit != 0))
				if (exec_logical(buff, mypath, i, envp) == 1)
					return (0);
			logical_operator(buff + i + 2, mypath, buff + i, envp);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*check_empty_logical(char *buff)
{
	int		i;
	char	print[3];

	if (buff == NULL)
		return (NULL);
	i = -1;
	while (buff[++i])
	{
		if (ft_strncmp(buff + i, "&&", 2) == 0
			|| ft_strncmp(buff + i, "||", 2) == 0)
		{
			if (buff[i + 2] == '&' || buff[i + 2] == '|')
			{
				strncpy(print, buff + i + 2, 2);
				printf("syntax error near unexpected token '%s'\n", print);
				return (NULL);
			}
			else if (check_emptyline(buff + i + 2) == 0)
				buff = ft_strjoin(buff, readline("> "));
		}
	}
	return (buff);
}
