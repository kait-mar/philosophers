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
