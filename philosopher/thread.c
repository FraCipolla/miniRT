/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabasset <mabasset@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:34:03 by mabasset          #+#    #+#             */
/*   Updated: 2022/04/15 18:34:03 by mabasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_fork(t_philo *ph)
{
	pthread_mutex_lock(ph->right);
	ft_philo_msg(ph->rules, ph->id, "has taken a fork");
	pthread_mutex_lock(ph->left);
	ft_philo_msg(ph->rules, ph->id, "has taken a fork");
}

void	*ft_meal(void *philo)
{
	t_philo *ph;

	ph = philo;
	if (ph->id % 2 == 0)
			usleep(ph->rules->time_eat * 1000);
	while (ph->finish == 0)
	{
		ft_take_fork(ph);
		ft_philo_msg(ph->rules, ph->id, "is eating");
		ph->n_eat++;
		usleep(ph->rules->time_eat * 1000);
		ph->starving = ft_time() - ph->rules->start;
		/* HO SPOSTATO IL SET A FINISH DOPO CHE PRENDE IL TEMPO DELLO STARVING,
			SE IL FILOSOFO HA FINITO DI MANGIARE IMPOSTA STARVING A -1, COSI VIENE ESCLUSO DAI FILOSOFI CHE POSSONO MORIRE */
		if (ph->n_eat == ph->rules->must_eat)
		{
			ph->starving = -1;
			ph->finish = 1;
		}
		pthread_mutex_unlock(ph->right);
		pthread_mutex_unlock(ph->left);
		ft_philo_msg(ph->rules, ph->id, "is sleeping");
		usleep(ph->rules->time_sleep * 1000);
		ft_philo_msg(ph->rules, ph->id, "is thinking");
	}
	return (NULL);
}

void	*ft_monitor(void *ru)
{
	int	i;
	long long	tmp;
	int 		check;
	t_rules		*rules;

	rules = ru;
	while(1)
	{
		tmp = ft_time() - rules->start;
		i = 0;
		check = 0;
		while(i < rules->n_ph)
		{
			/* HO MESSO UNA CONDIZIONE PER CUI NON DEVE CONSIDERARE I FILOSOFI CHE HANNO FINITO DI MANGIARE */
			if (rules->philo[i].starving > 0 && tmp - rules->philo[i].starving > rules->time_death)
			{
				ft_philo_msg(rules, rules->philo[i].id, "died");
				exit(0);
			}
			if (rules->philo[i].finish == 1)
				check++;
			i++;
		}
		/* CONDIZIONE PER FAR FINIRE IL PROGRAMMA NEL CASO TUTTI I FILOSOFI ABBIANO FINITO DI MANGIARE, CONTROLLA FT_MEAL */
		if (check == rules->n_ph)
			exit(0);
	}

	return (NULL);
}

void	ft_thread(t_rules *rules)
{
	int		i;
	t_philo	*philo;

	philo = rules->philo;
	rules->start = ft_time();
	i = 0;
	pthread_create(&rules->death, NULL, ft_monitor, rules);
	while (i < rules->n_ph)
	{
		pthread_create(&philo[i].thread, NULL, ft_meal, &philo[i]);
		i++;
	}
	pthread_join(rules->death, NULL);
	i = 0;
	while (i < rules->n_ph)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}