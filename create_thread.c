#include "philo.h"

t_philo *create_threads_core(t_philo philo, t_philo *all, pthread_t *threads)
{
    int i;

    i = 0;
    while (i < philo.num_philo)
    {
        gettimeofday(&all[i].start, NULL);
        all[i] = copy(all[i], philo);
        all[i].died = 0;
        all[i].id = i + 1;
        all[i].count_eat = 0;
        eat_times[i] = 0;
        if (pthread_create(&threads[i], NULL, &routine, &all[i]) != 0)
        {
            exit(EXIT_FAILURE);
        }
        i += 1;
    }
    return (all);
}

t_philo   *test(t_philo philo)
{
    t_philo   *threads;

    threads = malloc(sizeof(t_philo) * (philo.num_philo + 1));
    if (threads == NULL)
        printf("YEEEEEEESSSSS\n");
    return (threads);
}

t_philo   create_threads(t_philo philo)
{
    pthread_t   *threads;
	t_philo	*all;

	all = malloc(sizeof(t_philo) * (philo.num_philo + 1));
    threads = malloc(sizeof(pthread_t) * (philo.num_philo + 1));
    all = create_threads_core(philo, all, threads);
    all[philo.num_philo] = copy(all[philo.num_philo], philo);
    all[philo.num_philo].died = 0;
    if (pthread_create(&threads[philo.num_philo], NULL, &main_thread, &all[philo.num_philo]) != 0)
        return (philo);
    if (pthread_join(threads[philo.num_philo], NULL) != 0)
        printf("an error in join\n");
    return (philo);
}

int     verify(t_philo philo)
{
    int i = 0;

    while (i < philo.num_philo)
    {
        //printf("%d is on %d\n", i + 1, eat_times[i]);
        if (eat_times[i] < philo.eat_times || philo.eat_times == -1)
        {
            return (0);
        }
        i++;
    }
    printf("yes finished\n");
    /*int j = 0;
    while (j < philo.num_philo)
    {
        printf("%d ", eat_times[j++]);
    }
    printf("\n");*/
    died = 1;
    return (1);
}

void    *main_thread(void *ptr)
{
    t_philo philo;

    philo = *(t_philo *)ptr;
    while (1)
    {
        if (died == 1 || verify(philo) == 1)
            break ;
    }
    return (ptr);
}

