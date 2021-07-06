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

t_philo parse_arguments(int argc, char **argv)
{
    int i;
    t_philo philo;

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
    return (philo);
}

void    print_philo(t_philo philo)
{
    printf("we have [%d] philosopher\n", philo.num_philo);
    printf("[%ld] is time to die\n", philo.time_die);
    printf("[%ld] is time to eat\n", philo.time_eat);
    printf("[%ld] is time to sleep\n", philo.time_sleep);
    printf("[%ld] is eat times\n", philo.eat_times);
}
