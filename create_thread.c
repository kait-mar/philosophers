#include "philo.h"

t_thread   create_threads(t_philo philo)
{
    t_thread    tr;
    pthread_t   *threads;
    pthread_mutex_t  *forks;
	t_philo	*all;

    int i = 0;
	all = malloc(sizeof(t_philo) * philo.num_philo);
    while (i < philo.num_philo)
        gettimeofday(&all[i++].start, NULL);
    threads = malloc(sizeof(pthread_t) * philo.num_philo + 1);
    forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
    i = 0;
    tr.mutex = forks;
    while (i < philo.num_philo)
    {
        all[i] = copy(all[i], philo);
        all[i].died = 0;
        all[i].id = i + 1;
        all[i].count_eat = 0;
        eat_times[i] = 0;
        if ( pthread_create(&threads[i], NULL, &routine, &all[i]) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        i += 1;
    }
    all[i] = copy(all[i], philo);
    all[i].died = 0;
    if ( pthread_create(&threads[i + 1], NULL, &main_thread, &all[i]) != 0)
    {
        printf("%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    pthread_join(threads[i + 1], NULL);
   /* while (i < philo.num_philo)
    {
        pthread_join(threads[i], NULL);
        i += 1;
    }*/
    tr.threads = threads;
    return (tr);
}

int     verify(t_philo philo)
{
    int i = 0;

    while (i < philo.num_philo)
    {
        if (eat_times[i] < philo.eat_times || philo.eat_times == -1)
        {
            return (0);
        }
        i++;
    }
    return (1);
}

void    *main_thread(void *ptr)
{
    t_philo philo;

    philo = *(t_philo *)ptr;
    int i;

    i = 0;
    while (1)
    {
        if (died == 1 || verify(philo) == 1)
            break ;
    }
    return (ptr);
}
