#ifndef PHILO_H
# define PHILO_H
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>
//#include "./Libft/libft.h"

int *eat_times;
int died;
typedef struct s_philo
{
    int num_philo;
    long time_die;
    long time_eat;
    long time_sleep;
    long eat_times;
    pthread_mutex_t  *forks;
    pthread_mutex_t  *print;
    int id;
    int count_eat;
    int died;
    int life;
    int curent;
    struct timeval  start_eating;
    struct timeval  start;
}   t_philo;

// typedef struct s_thread
// {
//     pthread_t   *threads;
//     pthread_mutex_t  *mutex;
// }   t_thread;

void	print_error(void);
int	valid(char *argv);
int	valid2(char *argv, int *eat);
t_philo parse_arguments(int argc, char **argv);
void    print_philo(t_philo philo);
t_philo   create_threads(t_philo philo);
pthread_mutex_t *initialize_mutex(t_philo philo);
void    *routine(void *ptr);
long    micro_to_mill(long m);
long    mill_to_micro(long m);
t_philo eating_thread(t_philo philo);
void    my_sleep(long time);
t_philo verify_dying(t_philo philo);
int *initialize_flag(t_philo philo);
t_philo *fill_copy(t_philo *new, t_philo philo);
t_philo copy(t_philo new, t_philo philo);
long long get_time(t_philo philo);
long    diff(struct timeval tv, struct timeval current);
void    *main_thread(void *ptr);
int     verify(t_philo philo);
long	ft_atoi(const char *str);
t_philo *create_threads_core(t_philo philo, t_philo *all, pthread_t *threads);
long long get(struct timeval start);

#endif