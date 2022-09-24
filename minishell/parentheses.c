/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:24:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/25 00:16:50 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_parentheses(char *str)
{
	size_t	i;
	size_t	c;
	char	*ret;

	printf("str: %s\n", str);
	if (str[1] == ' ')
		i = 1;
	else
		i = 0;
	c = 0;
	ret = malloc(sizeof(char) * ft_strlen(str) - 2 - i);
	ret[ft_strlen(str) - 2 - i] = '\0';
	while (c < ft_strlen(str) - 2 - i)
		ret[c++] = str[++i];
	free(str);
	return (ret);
}

void	exec_subshell(char **args)
{
	char		**cmd;
	extern char	**environ;
	int			pid;

	pid = fork();
	if (pid == 0)
	{
		cmd = (char **)malloc(sizeof(char *) * 3);
		cmd[0] = "./minishell";
		cmd[1] = remove_parentheses(args[0]);
		cmd[2] = NULL;
		ft_increase_shlvl();
		execve(cmd[0], cmd, environ);
	}
	else
		waitpid(pid, NULL, 0);
}

int	between_parentheses(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '(')
		{
			while (str[++i])
			{
				if (str[i] == ')')
					return (0);
			}
		}
	}
	return (1);
}

int	logic_operator(char *buff)
{;
	if (ft_strncmp(buff, "&&", 2) == 0 || ft_strncmp(buff, "||", 2) == 0)
		return (2);
	if (buff[0] == '|' || buff[0] == '&')
		return(1);
	return (0);
}

char	*fill_parentheses(char *buff, int i)
{
	int		flag;
	char	*read;
	int		c;
	
	flag = 0;
	c = i;
	//	 SISTEMARE IL CASO DI ECHO( DEVE DARE ERROR, NON CONTROLLA BENE SE C'E' UN COMANDO FRA OPERATORE LOGICO E PARENTESI
	while (buff[i])
	{
		if (buff[i] == '(')
			if (strchr(buff + i, ')') == NULL)
				flag++;
		i++;
	}
	while (flag > 0)
	{
		read = readline("> ");
		if (strchr(read, ')') != NULL)
		{
			if (check_emptyline(buff + c) != 0)
				buff = ft_strjoin(buff, ";");
			buff = ft_strjoin(buff, " ");
			buff = ft_strjoin(buff, read);
			flag--;
		}
	}
	return (buff);
}

char	*check_empty_parentheses(char *buff)
{
	int		i;

	i = 0;
	while (buff[i] == ' ')
		i++;
	if (buff[i] != '(')
	{
		while (buff[i] && logic_operator(&buff[i]) == 0)
		{
			if (buff[i] == '(' || buff[i] == ')')
			{
				printf("bash: syntax error near unexpected token '%c'\n", buff[i]);
				return (NULL);
			}
			i++;
		}
		i += logic_operator(buff + i);
		while(buff[i] && buff[i] == ' ')
			i++;
	}
	return (fill_parentheses(buff, i));
}