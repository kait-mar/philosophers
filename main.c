#include "philo.h"

pthread_mutex_t  *forks;
int N;

t_philo parse_arguments(int argc, char **argv)
{
    int i;
    int j;
    t_philo philo;

    i = 1;
    philo.num_philo = valid(argv[i++]);
    philo.time_die = valid(argv[i++]);
    philo.time_eat = valid(argv[i++]);
    philo.time_sleep = valid(argv[i++]);
    if (argc - i == 0)
        return (philo);
    else if (argc - i != philo.num_philo)
        print_error();
    j = 0;
    philo.eat_times = malloc(sizeof(int) * philo.num_philo);
    while (j < philo.num_philo)
    {
        philo.eat_times[j++] = valid2(argv[i++], philo.eat_times);
    }
    return (philo);
}

void    print_philo(t_philo philo)
{
    int i;

    i = 0;
    printf("we have [%d] philosopher\n", philo.num_philo);
    printf("[%d] is time to die\n", philo.time_die);
    printf("[%d] is time to eat\n", philo.time_eat);
    printf("[%d] is time to sleep\n", philo.time_sleep);
    write(1, "[", 1);
    while (i < philo.num_philo)
        printf("%d ", philo.eat_times[i++]);
    write(1, "]", 1);
}

void    *func(void *ptr)
{
    t_philo philo;

    philo = *(t_philo *)ptr;
    if (N == philo.num_philo - 1)
    {
        pthread_mutex_lock(&forks[0]);
        pthread_mutex_lock(&forks[N]);
    }
    else
    {
        pthread_mutex_lock(&forks[N]);
        pthread_mutex_lock(&forks[N + 1]);
    }
    printf("%d has taken the two forks\n", N);
    printf("%d is eating\n", N);
    usleep(philo.time_eat);
    if (N == philo.num_philo - 1)
    {
        pthread_mutex_unlock(&forks[0]);
        pthread_mutex_unlock(&forks[N]);
    }
    else
    {
        pthread_mutex_unlock(&forks[N]);
        pthread_mutex_unlock(&forks[N + 1]);
    }
    N++;
    return (ptr);
}

t_thread   create_threads(t_philo philo)
{
    t_thread    tr;
    pthread_t   *threads;
    pthread_mutex_t  *forks;

    int i = 0;
    threads = malloc(sizeof(pthread_t) * philo.num_philo);
    forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
    int N = 0;
    tr.mutex = forks;
    while (N < philo.num_philo)
    {
        if ( pthread_create(&threads[N], NULL, &func, &philo) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        N++;
    }
    i = 0;
    while (i < philo.num_philo)
    {
        pthread_join(threads[i++], NULL);
    }
    tr.threads = threads;
    return (tr);
}

pthread_mutex_t *initialize_forks(t_philo philo)
{
    int i;
    pthread_mutex_t  *forks;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
    while (i < philo.num_philo)
    {
        if (pthread_mutex_init(&forks[i++], NULL) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    return (forks);
}

int main(int argc, char **argv)
{
    t_philo philosophers;
    t_thread   philo;

    philosophers = parse_arguments(argc, argv);
    forks = initialize_forks(philosophers);
    philo = create_threads(philosophers);
    return (1);
}
