/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/31 18:01:14 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include <stdio.h>

char	*command_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

void	child_one(t_px *pipex, char *argv[], char **envp, int *end)
{
	char	**mypath;
	char	**mycmdargs;
	int		i;
	char	*cmd;

	dup2(pipex->f1, STDIN_FILENO);
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	mypath = ft_split(command_path(envp), ':');
	mycmdargs = ft_split(argv[2], ' ');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	i = 0;
	while (mypath[i])
	{
		cmd = ft_strjoin(mypath[i], mycmdargs[0]);
		if (access(cmd, R_OK) == 0)
			break ;
		else
			free(cmd);
		i++;
	}
	execve(cmd, mycmdargs, envp);
}

void	child_two(t_px *pipex, char *argv[], char **envp, int *end)
{
	char	**mypath;
	char	**mycmdargs;
	int		i;
	char	*cmd;

	waitpid(-1, &pipex->status, 0);
	dup2(end[0], STDIN_FILENO);
	dup2(pipex->f2, STDOUT_FILENO);
	close(end[1]);
	mypath = ft_split(command_path(envp), ':');
	mycmdargs = ft_split(argv[3], ' ');
	i = -1;
	while (mypath[++i])
		mypath[i] = ft_strjoin(mypath[i], "/");
	i = 0;
	while (mypath[i])
	{
		cmd = ft_strjoin(mypath[i], mycmdargs[0]);
		if (access(cmd, R_OK) == 0)
			break ;
		else
			free(cmd);
		i++;
	}
	execve(cmd, mycmdargs, envp);
}

void	pipex(t_px *px, char *argv[], char **envp)
{
	int		end[2];
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one(px, argv, envp, end);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(px, argv, envp, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &px->status, 0);
	waitpid(child2, &px->status, 0);
}

int	main(int argc, char *argv[], char **envp)
{
	t_px	px;

	if (argc != 5)
		return (-1);
	px.f1 = open(argv[1], O_RDONLY);
	px.f2 = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (px.f1 < 0 || px.f2 < 0)
		return (-1);
	pipex(&px, argv, envp);
	return (0);
}
