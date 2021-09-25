#include "philo.h"

void    my_sleep(long time)
{
    struct timeval  current_time;
    struct timeval  tv;
    
    //gettimeofday(&current_time, NULL);
    usleep(mill_to_micro(time));
    /*while (1)
    {
        gettimeofday(&tv, NULL);
        //if (micro_to_mill((long)tv.tv_usec - (long)current_time.tv_usec) >= time)
        if (diff(tv, current_time) >= time)
            break ;
    }*/
}

t_philo verify_dying(t_philo philo)
{
    struct timeval tv;

    if (philo.died == 1 || died == 1)
    {
        int i = 0;
        while (i < philo.num_philo)
        {
            if (pthread_mutex_lock(&philo.forks[i]) != 0)
            printf("error in locking to die\n");
            i++;
        }
        //printf("%lld %d died mouad\n", get_time(philo), philo.id);
        //printf("%lld %d \n", get_time(philo), philo.id);
        philo.died = 1;
        died = 1;
        pthread_mutex_lock(&philo.print);
        printf("%lld %d died new dying2\n", get_time(philo), philo.id);
        //while (1);
        return (philo);
    }
    //printf("%d his last meal was in %ld\n", philo.id, diff(philo.start_eating, philo.start));
    gettimeofday(&tv, NULL);
    //printf(" with [%d] || start_eating=%ld | diff = %ld\n", philo.id, diff(philo.start_eating, philo.start), diff(tv, philo.start_eating));
    //printf("the curent is %lld and start_eating is %lld\n", get_time())
    //if (micro_to_mill((long)tv.tv_usec - (long)philo.start_eating.tv_usec) >= philo.time_die)
    //printf("T ==> %d || time_die ==> %ld\n", t, philo.time_die);
    //printf("%lld with [%d] diff is %ld\n", get_time(philo), philo.id, diff(tv, philo.start_eating));
    //printf("with [%d] the tv is %lld | and start_eating is %lld\n", philo.id, get(tv), get(philo.start_eating));
    if (diff(tv, philo.start_eating) > philo.time_die)
    {
        int i = 0;
        while (i < philo.num_philo)
        {
            if (pthread_mutex_lock(&philo.forks[i]) != 0)
                printf("error in locking to die\n");
            i++;
        }
        //printf("diff is %ld\n", diff(tv, philo.start_eating));
        // printf("%lld %d died kait\n", get_time(philo), philo.id);
        died = 1;
        philo.died = 1;
        pthread_mutex_lock(&philo.print);
         printf("%lld %d died kait\n", get_time(philo), philo.id);
        //while (1);
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

long long get(struct timeval start)
{
    //long long n;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    //n = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (diff(tv, start));
}

long    diff(struct timeval tv, struct timeval current)
{
    long    res1;
    long    res2;

    res1 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    res2 = (current.tv_sec * 1000) + (current.tv_usec / 1000);
    return (res1 - res2);
}
