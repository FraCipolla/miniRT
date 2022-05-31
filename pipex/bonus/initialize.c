/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/31 17:24:47 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	here_doc_pipex(t_px *pipex)
{
	char			*buff;
	static	char	*cmd;
	int				i;

	buff = NULL;
	pipex->heredoc_pipe = malloc(sizeof(int) * 2);
	pipe(pipex->heredoc_pipe);
	write(1, "heredoc> ", 9);
	while (1)
	{
		buff = get_next_line(0);
		if (ft_strcmp(buff, pipex->limiter) == 0)
			break;
		cmd = ft_strjoin(cmd, buff);
		cmd = ft_strjoin(cmd, "\n");
		write(1, "heredoc> ", 9);
		free(buff);
	}
	if (cmd == NULL)
		return ;
	i = 0;
	while (cmd[i] != '\0')
		i++;
	cmd[i - 1] = '\0';
	write(pipex->heredoc_pipe[1], cmd, ft_strlen(cmd));
	close(pipex->heredoc_pipe[1]);
}

void	here_doc_cmd(t_px *pipex)
{
	int	i;

	i = 0;
	while (pipex->mycmdargs[i + 1] != NULL)
	{
		pipex->mycmdargs[i] = pipex->mycmdargs[i + 1];
		i++;
	}
	pipex->mycmdargs[i] = NULL;
}

void    create_pipes(t_px *px)
{
    int i;

    i = 0;
	px->end = malloc(sizeof(int *) * px->n_cmd - 1);
    while (i < px->n_cmd - 1)
    {
        px->end[i] = malloc(sizeof(int) * 2);
        i++;
    }
    i = -1;
    while (++i < px->n_cmd - 1)
        pipe(px->end[i]);
}

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

int    init(int argc, char *argv[], char **envp, t_px *px)
{
    int		i;
	int		j;

    i  = 2;
	j = 0;
    px->n_cmd = argc - 3;
	if (px->n_cmd < 2)
		return (msgerror("need at least 2 commands"));
    px->mycmdargs = malloc(sizeof(char **) * argc - 3);
	px->mycmdargs[px->n_cmd] = NULL;
	px->mypath = ft_split(command_path(envp), ':');
	px->pid = malloc(sizeof(pid_t) * px->n_cmd);
	if (ft_strcmp(argv[1], "here_doc") != 0)
		px->f2 = open(argv[argc -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    while (i < argc - 1)
	{
		px->mycmdargs[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	i = -1;
	while (px->mypath[++i])
		px->mypath[i] = ft_strjoin(px->mypath[i], "/");
	return (0);
}