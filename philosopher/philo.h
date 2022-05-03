/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:39:36 by mabasset          #+#    #+#             */
/*   Updated: 2022/04/15 11:39:36 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				n_eat;
	int				finish;
	long long		starving;
	struct timeval	starve;
	struct s_rules	*rules;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_t		thread;
}				t_philo;

typedef struct s_rules
{
	int				n_ph;
	int				time_death;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_t		death;
	t_philo			*philo;
}				t_rules;

void		ft_error(char *str);
void		ft_philo_msg(t_rules *rules, int id, char *str);
int			ft_isspace(char c);
int			ft_atoi(const char *str);
int			ft_checker(int argc, char *argv[]);
long long	ft_time(void);
void		ft_thread(t_rules *rules);

#endif