/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:41:18 by kait-mar          #+#    #+#             */
/*   Updated: 2021/09/26 16:41:20 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *ptr)
{
	t_philo	philo;
	int		check;

	check = 0;
	philo = *(t_philo *)ptr;
	gettimeofday(&philo.start_eating, NULL);
	philo.curent = philo.start_eating.tv_sec * 1000
		+ philo.start_eating.tv_usec / 1000;
	if ((philo.id - 1) % 2 != 0 && philo.num_philo > 1)
	{
		if (philo.time_die < philo.time_eat)
			usleep(philo.time_die * 1000);
		else
			usleep(philo.time_eat * 1000);
	}
	while (1)
	{
		check = 1;
		philo = routine_support(philo);
		if (philo.died == 1 || g_died == 1)
			break ;
	}
	if (check == 0)
		printf("%lld %d died\n", get_time(philo), philo.id);
	return (ptr);
}

int	main(int argc, char **argv)
{
	t_philo	philosophers;

	if (argc > 6 || argc < 5)
	{
		printf("an error of arguments\n");
		return (1);
	}
	philosophers = parse_arguments(argc, argv);
	if (philosophers.num_philo == 1)
	{
		gettimeofday(&philosophers.start, NULL);
		printf("%lld 1 died\n", get_time(philosophers));
		return (1);
	}
	philosophers.id = 0;
	g_eat_times = initialize_flag(philosophers);
	g_died = 0;
	philosophers.forks = initialize_mutex(philosophers);
	if (pthread_mutex_init(&philosophers.print, NULL) != 0)
	{
		printf("error in initializing mutexes");
		exit(EXIT_FAILURE);
	}
	philosophers = create_threads(philosophers);
	return (1);
}

t_philo	routine_support(t_philo philo)
{
	philo = eating_thread(philo);
	philo = verify_dying(philo);
	if (philo.died == 1 || g_died == 1)
		return (philo);
	usleep(philo.time_sleep * 900);
	printf("%lld %d is sleeping\n", get_time(philo), philo.id);
	philo = verify_dying(philo);
	if (philo.died == 1 || g_died == 1)
		return (philo);
	printf("%lld %d is thinking\n", get_time(philo), philo.id);
	philo = verify_dying(philo);
	if (philo.died == 1 || g_died == 1)
		return (philo);
	return (philo);
}

long long	get(struct timeval start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (diff(tv, start));
}
