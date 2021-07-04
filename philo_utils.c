#include "philo.h"

long    micro_to_mill(long m)
{
    return (m * 0.001);
}

long    mill_to_micro(long m)
{
    return (m * 1000);
}

t_philo eating_thread(t_philo philo)
{
    if (verify_dying(philo) == 1)
    {
        philo.died = 1;
        return (philo);
    }
    philo.count_eat++;
    if (philo.id == philo.num_philo - 1)
    {
        if (pthread_mutex_lock(&philo.forks[0]) != 0
			|| pthread_mutex_lock(&philo.forks[philo.id]) != 0)
        {
			printf("error in locking a fork for %d | %s\n", philo.id + 1, strerror(errno));
		}
    }
    else
    {
		if (pthread_mutex_lock(&philo.forks[philo.id]) != 0
			|| pthread_mutex_lock(&philo.forks[philo.id + 1]) != 0)
		{
			printf("error in locking a fork for %d | %s\n", philo.id + 1, strerror(errno));
		}
    }
    printf("%d has taken the two forks\n", philo.id + 1);
    gettimeofday(&philo.start_eating, NULL);
    printf("%d is eating\n", philo.id + 1);
    my_sleep(philo.time_eat);
    if (philo.id == philo.num_philo - 1)
    {
		if (pthread_mutex_unlock(&philo.forks[0]) != 0
			|| pthread_mutex_unlock(&philo.forks[philo.id]) != 0)
			printf("error in unlocking a fork for %d | %s\n", philo.id + 1, strerror(errno));
    }
    else
    {
		if (pthread_mutex_unlock(&philo.forks[philo.id]) != 0 
			|| pthread_mutex_unlock(&philo.forks[philo.id + 1]) != 0)
			printf("error in unlocking a fork for %d | %s\n", philo.id + 1, strerror(errno));
    }
    return (philo);
}

int *initialize_flag(t_philo philo)
{
    int *f;
    int i;

    f = malloc(sizeof(int) * philo.num_philo);
    if (f == NULL)
        return (NULL);
    i = 0;
    while (i < philo.num_philo)
        f[i++] = -1;
    return (f);
}