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
    threads = malloc(sizeof(pthread_t) * philo.num_philo);
    forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
    i = 0;
    tr.mutex = forks;
    while (i < philo.num_philo)
    {
        all[i] = copy(all[i], philo);
        all[i].died = 0;
        all[i].id = i + 1;
        all[i].count_eat = 0;
        if ( pthread_create(&threads[i], NULL, &routine, &all[i]) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        i += 1;
    }
    i = 0;
    while (i < philo.num_philo)
    {
        pthread_join(threads[i], NULL);
        i += 1;
    }
    tr.threads = threads;
    return (tr);
}
