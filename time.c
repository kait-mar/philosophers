#include "philo.h"

void    my_sleep(long time)
{
    struct timeval  current_time;
    struct timeval  tv;
    
    gettimeofday(&current_time, NULL);
    usleep(mill_to_micro(time));
    while (1)
    {
        gettimeofday(&tv, NULL);
        //if (micro_to_mill((long)tv.tv_usec - (long)current_time.tv_usec) >= time)
        if (diff(tv, current_time) >= time)
            break ;
    }
}

t_philo verify_dying(t_philo philo)
{
    struct timeval tv;

    if (philo.died == 1 || died == 1)
    {
        /*if (pthread_mutex_lock(&philo.print[philo.id - 1]) != 0)
            printf("error in locking to die\n");*/
        printf("%lld %d died\n", get_time(philo), philo.id);
        //printf("%lld %d \n", get_time(philo), philo.id);
        philo.died = 1;
        died = 1;
        return (philo);
    }
    gettimeofday(&tv, NULL);
    if (micro_to_mill((long)tv.tv_usec - (long)philo.start_eating.tv_usec) >= philo.time_die)
    {
        printf("%lld %d died\n", get_time(philo), philo.id);
        died = 1;
        philo.died = 1;
        return (philo);
    }
    return (philo);
}

long long get_time(t_philo philo)
{
    //long long n;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    //n = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (diff(tv, philo.start));
}

long    diff(struct timeval tv, struct timeval current)
{
    long    res1;
    long    res2;

    res1 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    res2 = (current.tv_sec * 1000) + (current.tv_usec / 1000);
    return (res1 - res2);
}
