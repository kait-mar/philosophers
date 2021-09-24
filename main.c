#include "philo.h"

void    *routine(void *ptr)
{
    t_philo philo;
    int     check;

    check = 0;
    philo = *(t_philo *)ptr;
    gettimeofday(&philo.start_eating, NULL);
    philo.curent = philo.start_eating.tv_sec * 1000 + philo.start_eating.tv_usec / 1000;
    if ((philo.id - 1) % 2 != 0 && philo.num_philo > 1)
    {
        if (philo.time_die < philo.time_eat)
            my_sleep(philo.time_die);
        else
            my_sleep(philo.time_eat);
    }
	while (1)
	{
        check = 1;
        philo = eating_thread(philo);
		philo = verify_dying(philo);
		if (philo.died == 1 || died == 1)
			break ;
        //when use philo.forks instead, the opposite doesn't work !!!
        pthread_mutex_lock(&philo.print[philo.id - 1]);
		printf("%lld %d is sleeping\n", get_time(philo),  philo.id);
        pthread_mutex_unlock(&philo.print[philo.id - 1]);
		my_sleep(philo.time_sleep);
        philo = verify_dying(philo);
		if (philo.died == 1 || died == 1)
		{
			break ;
		}
        pthread_mutex_lock(&philo.print[philo.id - 1]);
		printf("%lld %d is thinking\n", get_time(philo),  philo.id);
        pthread_mutex_unlock(&philo.print[philo.id - 1]);
        philo = verify_dying(philo);
		if (philo.died == 1 || died == 1)
			break ;
        
	}
    if (check == 0)
    {
        /*if (pthread_mutex_lock(&philo.print[philo.id - 1]) != 0)
            printf("error in locking to die\n");*/
        printf("%lld %d died\n", get_time(philo), philo.id);
    }
    return (ptr);
}

pthread_mutex_t *initialize_mutex(t_philo philo)
{
    int i;

    i = 0;
    philo.forks = malloc(sizeof(pthread_mutex_t) * philo.num_philo);
    while (i < philo.num_philo)
    {
        if (pthread_mutex_init(&philo.forks[i++], NULL) != 0)
        {
            exit(EXIT_FAILURE);
        }
    }
    return (philo.forks);
}

int main(int argc, char **argv)
{
    t_philo philosophers;
    //t_thread   philo;

    if (argc > 6 || argc < 5)
    {
        printf("an error of arguments\n");
        return (1);
    }
    philosophers = parse_arguments(argc, argv);
	philosophers.id = 0;
    philosophers.died = 0;
	//flag = initialize_flag(philosophers);
	eat_times = initialize_flag(philosophers);
	died = 0;
    philosophers.forks = initialize_mutex(philosophers);
    philosophers.print = initialize_mutex(philosophers);
    philosophers = create_threads(philosophers);
    return (1);
}
