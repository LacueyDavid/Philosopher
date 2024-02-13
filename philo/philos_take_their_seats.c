/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_take_their_seats.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:33:22 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/13 15:38:03 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks_to_philo(t_philo *philo, int number_of_philos,
				pthread_mutex_t *forks)
{
	int	index;

	index = 0;
	while (index < number_of_philos)
	{
		philo[index].number_of_meals = 0;
		philo[index].left_fork = &forks[index];
		if (index == 0)
			philo[index].right_fork = &forks[number_of_philos - 1];
		else
			philo[index].right_fork = &forks[index - 1];
		index++;
	}
}

static void	assign_id_to_philo(t_philo *philo, int number_of_philosophers)
{
	int	index;

	index = 0;
	while (index < number_of_philosophers)
	{
		philo[index].id = index + 1;
		index++;
	}
}

static void	assign_table_to_philo(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		table->philos[index].table = table;
		table->philos[index].last_meal_time = get_time_in_ms();
		index++;
	}
}

void	philos_take_their_seats(t_table *table)
{
	assign_id_to_philo(table->philos, table->number_of_philosophers);
	assign_forks_to_philo(table->philos, table->number_of_philosophers,
		table->forks);
	assign_table_to_philo(table);
}
