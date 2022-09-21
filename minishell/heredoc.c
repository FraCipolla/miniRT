/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:33:53 by mcipolla          #+#    #+#             */
/*   Updated: 2022/09/21 15:34:31 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limiter, int *end)
{
	char	*buff;
	char	*ret;
	
	ret = NULL;
	while(1)
	{
		buff = readline("heredoc> ");
		if (strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
	}
	write (end[1], ret, ft_strlen(ret));
	close(end[1]);
	dup2(end[0], 0);
	free(buff);
}

char	*get_limiter(char **args)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (args[i])
	{
		if (ft_strcmp(args[i], "<<") == 0)
			ret = args[i + 1];
		i++;
	}
	return (ret);
}

int	here_doc_pipes(char	**args)
{
	char	*limiter;
	int		end[2];
	char	*buff;
	char	*ret;

	limiter = get_limiter(args);
	pipe(end);
	if (limiter == NULL)
		return (-1);
	ret = NULL;
	while(1)
	{
		buff = readline("heredoc> ");
		if (strcmp(buff, limiter) == 0)
			break ;
		ret = ft_strjoin(ret, buff);
		ret = ft_strjoin(ret, "\n");
	}
	write (end[1], ret, ft_strlen(ret));
	close(end[1]);
	free(buff);
	free(ret);
	return (end[0]);
}
