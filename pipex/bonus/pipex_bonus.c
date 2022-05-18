/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 17:12:52 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/18 16:35:03 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char    *command_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return(NULL);
}

void    child_one(t_px *pipex, char **envp, int *end)
{
	int     i;
	char    *cmd;

	dup2(pipex->f1, STDIN_FILENO);
	dup2(end[1], STDOUT_FILENO);
	close(end[0]);
	while (*pipex->mycmdargs)
	{
		i = 0;
		while (pipex->mypath[i])
		{
			cmd = ft_strjoin(pipex->mypath[i], *pipex->mycmdargs[0]);
			if (access(cmd, R_OK) == 0)
				execve(cmd, *pipex->mycmdargs, envp);
			else
				free(cmd);
			i++;
		}
		pipex->mycmdargs++;
	}
}

void    child_two(t_px *pipex, char *argv[], char **envp, int *end)
{
	char    **mycmdargs;
	int     i;
	char    *cmd;

	waitpid(-1, &pipex->status, 0);
	dup2(end[0], 0);
	dup2(pipex->f2, STDOUT_FILENO);
	close(end[1]);
	mycmdargs = ft_split(argv[pipex->arg - 1], ' ');
	i = 0;
	while (pipex->mypath[i])
	{
		cmd = ft_strjoin(pipex->mypath[i], mycmdargs[0]);
		if (access(cmd, R_OK) == 0)
			break ;
		else
			free(cmd);
		i++;
	}
	execve(cmd, mycmdargs, envp);
}

void    pipex(t_px *px, char *argv[], char **envp)
{
	int end[2];
	pid_t child1;
	pid_t child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
         return (perror("Fork: "));
	if (child1 == 0)
		child_one(px, envp, end);
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

int main(int argc, char *argv[], char **envp)
{
	t_px	px;
	int		i;

	if (argc < 5)
		return (-1);
	px.arg = argc;
	px.mycmdargs = malloc(sizeof(char **) * argc - 4);
	px.mypath = ft_split(command_path(envp), ':');
	px.f1 = open(argv[1], O_RDONLY);
	px.f2 = open(argv[argc -1], O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (px.f1 < 0 || px.f2 < 0)
		return (-1);
	i  = 2;
	while (i < argc - 2)
	{
		*px.mycmdargs = ft_split(argv[i], ' ');
		px.mycmdargs++;
		i++;
	}
	i = -1;
	while (px.mypath[++i])
		px.mypath[i] = ft_strjoin(px.mypath[i], "/");
	pipex(&px, argv, envp);
	return (0);
}