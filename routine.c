#include "philo.h"

void	eat(t_philo *philo)
{
	// prend les fourchettes pour manger
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	// mange
	print_message(philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	// relache les fourchettes
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	eepy(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void *philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		eat(philo);
		eepy(philo);
		think(philo);
	}
	return (NULL);
}
