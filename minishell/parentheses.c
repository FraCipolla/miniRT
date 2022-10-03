/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 21:24:05 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/03 18:01:35 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_parentheses(char *str)
{
	size_t	i;
	size_t	c;
	char	*ret;
	size_t	size;

	if (str[1] == ' ')
	{
		size = ft_strlen(str) - 3;
		i = 2;
	}
	else
	{
		size = ft_strlen(str) - 2;
		i = 1;
	}
	c = -1;
	ret = malloc(sizeof(char) * size);
	ret[size] = '\0';
	while (++c < size)
	{
		ret[c] = str[i];
		i++;
	}
	free(str);
	return (ret);
}

void	exec_subshell(char **args, char **envp)
{
	char		**cmd;
	int			pid;
	int			status;

	cmd = (char **)malloc(sizeof(char *) * 3);
	cmd[0] = ft_strdup("./minishell");
	cmd[1] = remove_parentheses(args[0]);
	cmd[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		ft_increase_shlvl();
		execve(cmd[0], cmd, envp);
	}
	else
	{
		waitpid(pid, &status, 0);
		my_free(cmd);
		free(args);
		set_global(status);
	}
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
{
	if (ft_strncmp(buff, "&&", 2) == 0 || ft_strncmp(buff, "||", 2) == 0)
		return (2);
	if (buff[0] == '|' || buff[0] == '&')
		return (1);
	return (0);
}

char	*fill_parentheses(char *buff, int i)
{
	int		flag;
	char	*read;
	int		c;

	flag = 0;
	c = i;
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
		if (check_emptyline(buff + c + 1) != 0)
			buff = ft_strjoin(buff, ";");
		buff = ft_strjoin(buff, " ");
		buff = ft_strjoin(buff, read);
		if (strchr(read, ')') != NULL)
			flag--;
		free(read);
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
				printf("syntax error near unexpected token '%c'\n", buff[i]);
				return (NULL);
			}
			i++;
		}
		i += logic_operator(buff + i);
		while (buff[i] && buff[i] == ' ')
			i++;
	}
	return (fill_parentheses(buff, i));
}
