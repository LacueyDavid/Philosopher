/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:38:44 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/16 18:38:46 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

static bool	odd_philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork), true);
	pthread_mutex_lock(philo->right_fork);
	if (print_message(philo, "has taken a fork"))
		return (unlock_forks(philo));
	if (print_message(philo, "is eating"))
		return (unlock_forks(philo));
	pthread_mutex_lock(&philo->number_of_meals_mutex);
	philo->number_of_meals++;
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->number_of_meals_mutex);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (false);
}

static bool	pair_philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	if (print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->right_fork), true);
	pthread_mutex_lock(philo->left_fork);
	if (print_message(philo, "has taken a fork"))
		return (unlock_forks(philo));
	if (print_message(philo, "is eating"))
		return (unlock_forks(philo));
	pthread_mutex_lock(&philo->number_of_meals_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->number_of_meals++;
	pthread_mutex_unlock(&philo->number_of_meals_mutex);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (false);
}

static bool	philosopher_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
		return (odd_philosopher_eat(philo));
	return (pair_philosopher_eat(philo));
}

static bool	philosopher_sleep(t_philo *philo)
{
	if (print_message(philo, "is sleeping"))
		return (true);
	ft_usleep(philo->table->time_to_sleep);
	return (false);
}

static bool	philosopher_think(t_philo *philo)
{
	int	time;
	if (print_message(philo, "is thinking"))
		return (true);
	if (philo->table->number_of_philosophers % 2 == 0)
		time = philo->table->time_to_eat - philo->table->time_to_sleep;
	else
		time = 2 * philo->table->time_to_eat - philo->table->time_to_sleep;
	if (time > 0)
		ft_usleep(time);
	return (false);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_message(philo, "is thinking");
	if (philo->id % 2 == 0)
		ft_usleep(2);
	while (!is_the_meal_over(philo))
	{
		if (philosopher_eat(philo))
			break ;
		if (philosopher_sleep(philo))
			break ;
		if (philosopher_think(philo))
			break ;
	}
	return (NULL);
}
