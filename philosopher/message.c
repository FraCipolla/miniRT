/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcipolla <mcipolla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 22:54:42 by mabasset          #+#    #+#             */
/*   Updated: 2022/05/03 11:58:17 by mcipolla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_philo_msg(t_rules *rules, int id, char *str)
{
	pthread_mutex_lock(&rules->lock);
	printf("%lld ", ft_time() - rules->start);
	printf("philosopher %d %s\n", id, str);
	pthread_mutex_unlock(&rules->lock);
}
