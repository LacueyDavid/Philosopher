/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:38:44 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/13 16:02:37 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (true);
}

static bool	philosopher_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (print_message(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->left_fork), true);
	pthread_mutex_lock(philo->right_fork);
	if (print_message(philo, "has taken a fork"))
		return (unlock_forks(philo));
	if (is_the_meal_over(philo))
		return (unlock_forks(philo));
	if (print_message(philo, "is eating"))
		return (unlock_forks(philo));
	philo->number_of_meals++;
	ft_usleep(philo->table->time_to_eat);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (false);
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
	if (print_message(philo, "is thinking"))
		return (true);
	return (false);
}

void	*philosophers_routine(void *arg)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		ft_usleep(1);
	philosopher_think(philo);
	while (!is_the_meal_over(philo))
	{
		if (philosopher_eat(philo))
			break ;
		if (philosopher_sleep(philo))
			break ;
		if (philosopher_think(philo))
			break ;
	}
	time = get_time_in_ms() - philo->table->dinner_start_time;
	if (philo->id == philo->table->sign_of_death)
		printf("%ld %ld %s\n", time, philo->table->sign_of_death, "died");
	return (NULL);
}
