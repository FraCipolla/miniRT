/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:08:41 by mcipolla          #+#    #+#             */
/*   Updated: 2022/10/06 19:18:10 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_pipes(char *str, char **mypath, char **args, char **envp)
{
	char	**pipes;
	int		matrix_size;
	int		n_pipes;

	matrix_size = 0;
	pipes = ft_split(str, '|');
	while (pipes[matrix_size])
		matrix_size++;
	n_pipes = matrix_size - 1;
	if (matrix_size > 1)
		pipex(pipes, n_pipes, envp);
	else
		split_exec(mypath, args, envp);
	my_free(pipes);
}

char	*first_check(char *buff)
{
	char	*tmp;

	if (buff == NULL)
		msg_exit();
	if (buff[0] == '\0')
		return (buff);
	tmp = buff;
	buff = check_empty_parentheses(buff);
	if (buff == NULL)
		add_history(tmp);
	else
		add_history(buff);
	buff = check_empty_logical(buff);
	buff = ft_addspaces(buff);
	if (buff == NULL)
	{
		buff = ft_strdup("");
		g_exit = 258;
	}
	return (buff);
}

void	start_parsing(char *buff, char **mypath, char **envp)
{
	char	**args;
	char	**args2;
	int		i;
	int		c;

	i = 0;
	args = ft_split(buff, ';');
	while (args[i])
	{
		args2 = ft_split(args[i], ' ');
		c = -1;
		while (args2[++c])
		{
			if (args2[c][0] == '$')
			{
				free(args2[c]);
				args2[c] = ft_strdup(getenv(&args2[c][1]));
			}
		}
		args2 = check_wild(args2);
		if (args2 == NULL)
			return ;
		if (logical_operator(args[i], mypath, NULL, envp) == 1)
			check_pipes(args[i], mypath, remove_quotes(args2), envp);
		my_free(args2);
		i++;
	}
	my_free(args);
}

int	main(int argc, char *argv[], char **envp)
{
	char		*buff;
	char		**mypath;
	extern char	**environ;

	// clt_echo("-ctlecho");
	mypath = NULL;
	while (1)
	{
		init();
		environ = envp;
		mypath = get_path();
		if (argc > 1)
			buff = argv[1];
		else
		{
			buff = readline("minishell: ");
			buff = first_check(buff);
		}
		if (buff[0] != '\0')
			start_parsing(buff, mypath, envp);
		if (argc > 1)
			exit(g_exit);
		free(buff);
		if (mypath)
			my_free(mypath);
	}
	return (g_exit);
}
