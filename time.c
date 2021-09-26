/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:42:28 by kait-mar          #+#    #+#             */
/*   Updated: 2021/09/26 16:42:31 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	verify_dying(t_philo philo)
{
	struct timeval	tv;
	int				i;

	if (philo.died == 1 || g_died == 1)
	{
		i = 0;
		while (i < philo.num_philo)
		{
			pthread_mutex_lock(&philo.forks[i]);
			i++;
		}
		philo.died = 1;
		g_died = 1;
		pthread_mutex_lock(&philo.forks[philo.id + 1]);
		printf("%lld %d died\n", get_time(philo), philo.id);
		return (philo);
	}
	gettimeofday(&tv, NULL);
	if (diff(tv, philo.start_eating) > philo.time_die)
		return (verify_dying_support(philo));
	return (philo);
}

t_philo	verify_dying_support(t_philo philo)
{
	int	i;

	i = 0;
	while (i < philo.num_philo)
	{
		pthread_mutex_lock(&philo.forks[i]);
		i++;
	}
	g_died = 1;
	philo.died = 1;
	pthread_mutex_lock(&philo.forks[philo.id + 1]);
	printf("%lld %d died\n", get_time(philo), philo.id);
	return (philo);
}

long long	get_time(t_philo philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_time2(t_philo philo)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (diff(tv, philo.start));
}

long	diff(struct timeval tv, struct timeval current)
{
	long	res1;
	long	res2;

	res1 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	res2 = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (res1 - res2);
}
