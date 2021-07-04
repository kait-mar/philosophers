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
        if (micro_to_mill((long)tv.tv_usec - (long)current_time.tv_usec) >= time)
            break ;
    }
}

int verify_dying(t_philo philo)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (micro_to_mill((long)tv.tv_usec - (long)philo.start_eating.tv_usec) >= philo.time_die)
    {
        printf("%d has died\n", philo.id);
        died = 1;
        return (1);
    }
    return (0);
}
