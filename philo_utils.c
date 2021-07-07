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

t_philo copy(t_philo new, t_philo philo)
{
    new.eat_times = philo.eat_times;
    new.time_die = philo.time_die;
    new.time_eat = philo.time_eat;
    new.time_sleep = philo.time_sleep;
    new.num_philo = philo.num_philo;
    new.forks = philo.forks;
    return (new);
}

t_philo eating_thread(t_philo philo)
{
    philo = verify_dying(philo);
    if (philo.died == 1 || died == 1)
    {
        return (philo);
    }
    eat_times[philo.id - 1] += 1;
    if (philo.id == philo.num_philo)
    {
        if (pthread_mutex_lock(&philo.forks[0]) != 0
			|| pthread_mutex_lock(&philo.forks[philo.id - 1]) != 0)
        {
			printf("error in locking a fork for %d\n", philo.id);
            //return (philo);
		}
    }
    else
    {
		if (pthread_mutex_lock(&philo.forks[philo.id - 1]) != 0
			|| pthread_mutex_lock(&philo.forks[philo.id]) != 0)
		{
			printf("error in locking a fork for %d\n", philo.id);
            //return (philo);
		}
    }
    if (philo.died == 0 && died == 0)
    {
        printf("%lld %d has taken a fork\n", get_time(philo), philo.id);
        printf("%lld %d has taken a fork\n", get_time(philo), philo.id);
    }
    else
        return (philo);
    /*printf("%d has taken a fork\n", philo.id);
    printf("%d has taken a fork\n", philo.id);*/
    //gettimeofday(&philo.start_eating, NULL);
     if (philo.died == 0 && died == 0)
     {
         //gettimeofday(&philo.start_eating, NULL);
         gettimeofday(&philo.start_eating, NULL);
         philo.curent = philo.start_eating.tv_sec * 1000 + philo.start_eating.tv_usec / 1000; 
         printf("%lld %d is eating\n", get_time(philo),philo.id);
     }
    else
        return (philo);
    my_sleep(philo.time_eat);
   // printf("the time is %lld\n", get_time(philo));
    if (philo.id == philo.num_philo)
    {
		if (pthread_mutex_unlock(&philo.forks[0]) != 0
			|| pthread_mutex_unlock(&philo.forks[philo.id - 1]) != 0)
			printf("error in unlocking a fork for %d\n", philo.id);

    }
    else
    {
		if (pthread_mutex_unlock(&philo.forks[philo.id - 1]) != 0 
			|| pthread_mutex_unlock(&philo.forks[philo.id]) != 0)
			printf("error in unlocking a fork for %d\n", philo.id);
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
