#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>
#include "./Libft/libft.h"

int *N;
int *flag;
int died;
typedef struct s_philo
{
    int num_philo;
    long time_die;
    long time_eat;
    long time_sleep;
    int *eat_times;
    pthread_mutex_t  *forks;
    int id;
    int count_eat;
    int died;
    struct timeval  start_eating;
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
void    *routine(void *ptr);
long    micro_to_mill(long m);
long    mill_to_micro(long m);
t_philo eating_thread(t_philo philo);
void    my_sleep(long time);
int verify_dying(t_philo philo);
int *initialize_flag(t_philo philo);
t_philo *fill_copy(t_philo *new, t_philo philo);

#endif