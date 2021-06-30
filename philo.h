#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include "./Libft/libft.h"

typedef struct s_philo
{
    int num_philo;
    int time_die;
    int time_eat;
    int time_sleep;
    int *eat_times;
}   t_philo;
typedef struct s_thread
{
    pthread_t   *threads;
    pthread_mutex_t  *mutex;
}   t_thread;

void	print_error(void);
int	valid(char *argv);
int	valid2(char *argv, int *eat);
t_philo parse_arguments(int argc, char **argv);
void    print_philo(t_philo philo);
t_thread   create_threads(t_philo philo);
pthread_mutex_t *initialize_forks(t_philo philo);


#endif