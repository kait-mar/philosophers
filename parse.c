/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kait-mar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:41:36 by kait-mar          #+#    #+#             */
/*   Updated: 2021/09/26 16:41:38 by kait-mar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	valid(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!((argv[i] >= '0' && argv[i] <= '9')
				|| ((argv[i] == '-' || argv[i] == '+')
					&& (argv[i + 1] >= '0' && argv[i + 1] <= '9')))
			|| ((argv[i] >= '0' && argv[i] <= '9')
				&& (argv[i + 1] == '-' || argv[i + 1] == '+')))
			print_error();
		i++;
	}
	return (ft_atoi(argv));
}

int	valid2(char *argv, int *eat)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!((argv[i] >= '0' && argv[i] <= '9')
				|| ((argv[i] == '-' || argv[i] == '+')
					&& (argv[i + 1] >= '0' && argv[i + 1] <= '9')))
			|| ((argv[i] >= '0' && argv[i] <= '9')
				&& (argv[i + 1] == '-' || argv[i + 1] == '+')))
		{
			free(eat);
			print_error();
		}
		i++;
	}
	return (ft_atoi(argv));
}

t_philo	parse_arguments(int argc, char **argv)
{
	int		i;
	t_philo	philo;

	i = 1;
	philo.num_philo = valid(argv[i++]);
	philo.time_die = valid(argv[i++]);
	philo.time_eat = valid(argv[i++]);
	philo.time_sleep = valid(argv[i++]);
	if (argc - i == 0)
	{
		philo.eat_times = -1;
		return (philo);
	}
	philo.eat_times = valid(argv[i++]);
	philo.died = 0;
	return (philo);
}
