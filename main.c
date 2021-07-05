#include "philo.h"

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
    printf("[%ld] is time to die\n", philo.time_die);
    printf("[%ld] is time to eat\n", philo.time_eat);
    printf("[%ld] is time to sleep\n", philo.time_sleep);
    write(1, "[", 1);
    while (i < philo.num_philo)
        printf("%d ", philo.eat_times[i++]);
    write(1, "]", 1);
}

void    *routine(void *ptr)
{
    t_philo philo;
    int     check;

    check = 0;
    philo = *(t_philo *)ptr;
    if ((philo.id - 1) % 2 != 0)
    {
        printf("yes with %d\n", philo.id);
        my_sleep(100);
    }
    gettimeofday(&philo.start_eating, NULL);
	while (philo.died != 1 && died != 1)
	{
        check = 1;
		philo = eating_thread(philo);
		philo = verify_dying(philo);
		if (philo.died == 1 || died == 1)
		{
			break ;
		}
		printf("%lld %d is sleeping\n", get_time(philo),  philo.id);
		//can he die while sleeping ? !! I think yes
		my_sleep(philo.time_sleep);
        philo = verify_dying(philo);
		if (philo.died == 1 || died == 1)
		{
			break ;
		}
		printf("%lld %d is thinking\n", get_time(philo),  philo.id);
	}
    if (check == 0)
    {
        /*if (pthread_mutex_lock(&philo.print[philo.id - 1]) != 0)
            printf("error in locking to die\n");*/
        printf("%lld %d died\n", get_time(philo), philo.id);
    }
    return (ptr);
}

/*t_thread   create_threads(t_philo philo)
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
        //N = malloc(sizeof(int));
		//N[j++] = i;
        all[i] = copy(all[i], philo);
        all[i].died = 0;
        all[i].id = i + 1;
        all[i].count_eat = 0;
        //new = malloc(sizeof(t_philo));
        //new = fill_copy(new, philo);
        //new->id = i + 1;
		//new->count_eat = 0;
        //new->died = 0;
        if ( pthread_create(&threads[i], NULL, &routine, &all[i]) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
		//usleep(160000);
        i += 2;
    }
    i = 0;
    while (i < philo.num_philo)
    {
        pthread_join(threads[i], NULL);
        i += 2;
    }
    i = 1;
    while (i < philo.num_philo)
    {
		//all[i] = malloc(sizeof(t_philo));
        //N = malloc(sizeof(int));
		//N[j++] = i;
		all[i] = copy(all[i], philo);
        all[i].died = 0;
        all[i].id = i + 1;
        all[i].count_eat = 0;
        //new = malloc(sizeof(t_philo));
        //new = fill_copy(new, philo);
        //new->id = i + 1;
		//new->count_eat = 0;
        //new->died = 0;
        if (pthread_create(&threads[i], NULL, &routine, &all[i]) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
		//usleep(160000);
        i += 2;
		//printf("n is %d\n", N);
    }
    i = 1;
    while (i < philo.num_philo)
    {
        pthread_join(threads[i], NULL);
        i += 2;
    }
    tr.threads = threads;
    return (tr);
}*/

pthread_mutex_t *initialize_mutex(t_philo philo)
{
    int i;

    i = 0;
    philo.forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
    while (i < philo.num_philo)
    {
        if (pthread_mutex_init(&philo.forks[i++], NULL) != 0)
        {
            printf("%s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
    return (philo.forks);
}

int main(int argc, char **argv)
{
    t_philo philosophers;
    t_thread   philo;

    philosophers = parse_arguments(argc, argv);
	philosophers.id = 0;
    philosophers.died = 0;
	//flag = initialize_flag(philosophers);
	N = initialize_flag(philosophers);
	died = 0;
    philosophers.forks = initialize_mutex(philosophers);
    philosophers.print = initialize_mutex(philosophers);
    philo = create_threads(philosophers);
    return (1);
}
