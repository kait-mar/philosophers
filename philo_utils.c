#include "philo.h"

long    micro_to_mill(long m)
{
    return (m * 0.001);
}

long    mill_to_micro(long m)
{
    return (m * 1000);
}

t_philo *fill_copy(t_philo *new, t_philo philo)
{
    new->eat_times = philo.eat_times;
    new->time_die = philo.time_die;
    new->time_eat = philo.time_eat;
    new->time_sleep = philo.time_sleep;
    new->num_philo = philo.num_philo;
    new->forks = philo.forks;
    return (new);
}

t_philo eating_thread(t_philo philo)
{
    if (verify_dying(philo) == 1)
    {
        philo.died = 1;
        return (philo);
    }
    philo.count_eat++;
    if (philo.id == philo.num_philo)
    {
        if (pthread_mutex_lock(&philo.forks[0]) != 0
			|| pthread_mutex_lock(&philo.forks[philo.id - 1]) != 0)
        {
			printf("error in locking a fork for %d | %s\n", philo.id, strerror(errno));
		}
    }
    else
    {
		if (pthread_mutex_lock(&philo.forks[philo.id - 1]) != 0
			|| pthread_mutex_lock(&philo.forks[philo.id]) != 0)
		{
			printf("error in locking a fork for %d | %s\n", philo.id, strerror(errno));
		}
    }
    printf("%d has taken the two forks\n", philo.id);
    gettimeofday(&philo.start_eating, NULL);
    printf("%d is eating\n", philo.id);
    my_sleep(philo.time_eat);
    if (philo.id == philo.num_philo)
    {
		if (pthread_mutex_unlock(&philo.forks[0]) != 0
			|| pthread_mutex_unlock(&philo.forks[philo.id - 1]) != 0)
			printf("error in unlocking a fork for %d | %s\n", philo.id, strerror(errno));
    }
    else
    {
		if (pthread_mutex_unlock(&philo.forks[philo.id - 1]) != 0 
			|| pthread_mutex_unlock(&philo.forks[philo.id]) != 0)
			printf("error in unlocking a fork for %d | %s\n", philo.id, strerror(errno));
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