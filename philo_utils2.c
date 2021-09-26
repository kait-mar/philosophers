/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:42:12 by kait-mar          #+#    #+#             */
/*   Updated: 2021/09/26 16:42:14 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*initialize_mutex(t_philo philo)
{
	int	i;

	i = 0;
	philo.forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
	while (i < philo.num_philo)
	{
		if (pthread_mutex_init(&philo.forks[i++], NULL) != 0)
		{
			exit(EXIT_FAILURE);
		}
	}
	return (philo.forks);
}

long	mill_to_micro(long m)
{
	return (m * 1000);
}

t_philo	*fill_copy(t_philo *new, t_philo philo)
{
	new->eat_times = philo.eat_times;
	new->time_die = philo.time_die;
	new->time_eat = philo.time_eat;
	new->time_sleep = philo.time_sleep;
	new->num_philo = philo.num_philo;
	new->forks = philo.forks;
	return (new);
}

t_philo	copy(t_philo new, t_philo philo)
{
	new.eat_times = philo.eat_times;
	new.time_die = philo.time_die;
	new.time_eat = philo.time_eat;
	new.time_sleep = philo.time_sleep;
	new.num_philo = philo.num_philo;
	new.forks = philo.forks;
	new.print = philo.print;
	return (new);
}

int	*initialize_flag(t_philo philo)
{
	int	*f;
	int	i;

	f = malloc(sizeof(int) * philo.num_philo);
	if (f == NULL)
		return (NULL);
	i = 0;
	while (i < philo.num_philo)
		f[i++] = -1;
	return (f);
}
