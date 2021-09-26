/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:41:58 by kait-mar          #+#    #+#             */
/*   Updated: 2021/09/26 16:42:00 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	micro_to_mill(long m)
{
	return (m * 0.001);
}

t_philo	eating_thread(t_philo philo)
{
	struct timeval	tv;

	if (pthread_mutex_lock(&philo.forks[philo.id % philo.num_philo]) != 0
		|| pthread_mutex_lock(&philo.forks[(philo.id - 1)
				% philo.num_philo]) != 0)
		printf("error in locking a fork for %d\n", philo.id);
	gettimeofday(&tv, NULL);
	if (diff(tv, philo.start_eating) > philo.time_die)
	{
		g_died = 1;
		philo.died = 1;
		pthread_mutex_lock(&philo.forks[philo.id + 1]);
		printf("%lld %d died\n", get_time(philo), philo.id);
		return (philo);
	}
	philo = eating_support(philo);
	if (verify(philo) == 1)
		philo.died = 1;
	return (philo);
}

t_philo	eating_support(t_philo philo)
{
	printf("%lld %d has taken a fork\n", get_time(philo), philo.id);
	printf("%lld %d has taken a fork\n", get_time(philo), philo.id);
	printf("%lld %d is eating\n", get_time(philo), philo.id);
	gettimeofday(&philo.start_eating, NULL);
	usleep(philo.time_eat * 900);
	g_eat_times[philo.id - 1] += 1;
	if (pthread_mutex_unlock(&philo.forks[philo.id % philo.num_philo]) != 0
		|| pthread_mutex_unlock(&philo.forks[(philo.id - 1)
				% philo.num_philo]) != 0)
		printf("error in unlocking a fork for %d\n", philo.id);
	return (philo);
}
