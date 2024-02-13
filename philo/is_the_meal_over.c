/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_the_meal_over.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:44:19 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/13 15:44:47 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	a_philosophe_die_of_starvation(t_philo *philo)
{
	if (get_time_in_ms() - philo->last_meal_time > philo->table->time_to_die)
	{
		pthread_mutex_lock(&philo->table->write_to_sign_of_death);
		if (philo->table->sign_of_death)
		{
			pthread_mutex_unlock(&philo->table->write_to_sign_of_death);
			return (true);
		}
		philo->table->sign_of_death = philo->id;
		pthread_mutex_unlock(&philo->table->write_to_sign_of_death);
		return (true);
	}
	return (false);
}

static bool	sign_of_death_is_set(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->write_to_sign_of_death);
	if (philo->table->sign_of_death)
	{
		pthread_mutex_unlock(&philo->table->write_to_sign_of_death);
		return (true);
	}
	pthread_mutex_unlock(&philo->table->write_to_sign_of_death);
	return (false);
}

bool	is_the_meal_over(t_philo *philo)
{
	if (sign_of_death_is_set(philo))
		return (true);
	else if (a_philosophe_die_of_starvation(philo))
		return (true);
	else if (philo->table->times_each_philosopher_must_eat == -1)
		return (false);
	else if ((int)philo->number_of_meals
		>= philo->table->times_each_philosopher_must_eat)
		return (true);
	return (false);
}
