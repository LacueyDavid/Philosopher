#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef MAX_PHILOS
# define MAX_PHILOS 200
#endif

// Structures

struct s_table;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	size_t			dinner_start_time;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_each_philosopher_must_eat;
	pthread_mutex_t	forks[MAX_PHILOS];
	t_philo			philos[MAX_PHILOS];
}	t_table;

// arguments validity
bool	check_arguments_validity(int argc, char **argv);

// Libft
bool	ft_isdigit(int c);
int		ft_atoi(const char *nptr);

// initialisation des viriables
bool	prepare_the_table(t_table *table, int argc, char **argv);

// cleaning
void	clean_the_forks(t_table *table, int size_to_clear);
void	kill_every_philosophers(t_table *table, int size_to_clear);
void	clean_the_table(t_table *table);

// dinner
bool	start_the_dinner(t_table *table);

// routine
void *philosophers_routine(void *arg);

// get_time
size_t	get_time_in_ms();

// sleep
void	ft_usleep(size_t time_in_ms);

// print for philo
void   print_message(t_philo *philo, char *message);

#endif
