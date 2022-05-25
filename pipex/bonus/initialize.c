/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:32:21 by mcipolla          #+#    #+#             */
/*   Updated: 2022/05/25 19:04:07 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

void    init(int argc, char *argv[], char **envp, t_px *px)
{
    int		i;
	int		j;

    i  = 2;
	j = 0;
    px->n_cmd = argc - 3;
    px->mycmdargs = malloc(sizeof(char **) * argc - 3);
	px->mycmdargs[px->n_cmd] = NULL;
	px->mypath = ft_split(command_path(envp), ':');
	px->f1 = open(argv[1], O_RDONLY);
	px->f2 = open(argv[argc -1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	px->pid = malloc(sizeof(pid_t) * px->n_cmd);
    while (i < argc - 1)
	{
		px->mycmdargs[j] = ft_split(argv[i], ' ');
		i++;
		j++;
	}
	i = -1;
	while (px->mypath[++i])
		px->mypath[i] = ft_strjoin(px->mypath[i], "/");
}