/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_dinner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:50:38 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/14 18:43:14 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *print_dead(void *arg)
{
	t_table *table;
	size_t	time;

	table = (t_table *)arg;
	while(true)
	{
		time = get_time_in_ms() - table->dinner_start_time;
		pthread_mutex_lock(&table->write_to_sign_of_death);
		if (table->sign_of_death)
		{
			printf("%ld %ld %s\n", time, table->sign_of_death, "died");
			pthread_mutex_unlock(&table->write_to_sign_of_death);
			break;
		}
		pthread_mutex_unlock(&table->write_to_sign_of_death);
	}
	return table;
}

static bool	philosophers_start_their_routine(t_table *table)
{
	size_t	index;

	index = 0;
	if (pthread_create(&table->thread, NULL, &print_dead, table) != 0)
	{
		clean_the_forks(table, table->number_of_philosophers);
		return (false);
	}
	while (index < table->number_of_philosophers)
	{
		if (pthread_create(&table->philos[index].thread, NULL,
						   &philosophers_routine, &table->philos[index]) != 0)
		{
			clean_the_forks(table, table->number_of_philosophers);
			return (false);
		}
		index++;
	}
	return (true);
}

static bool	wait_philosophers_finish_their_dinner(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_join(table->philos[index].thread, NULL) != 0)
		{
			printf("Error: pthread_join() failed\n");
			clean_the_table(table);
			return (false);
		}
		index++;
	}
	if (pthread_join(table->thread, NULL) != 0)
	{
		printf("Error: pthread_join() failed\n");
		clean_the_table(table);
		return (false);
	}
	return (true);
}

bool	start_the_dinner(t_table *table)
{
	if (table->number_of_philosophers == 1)
	{
		ft_usleep(table->time_to_die);
		print_message(&table->philos[0], "died.");
		return (true);
	}
	if (!philosophers_start_their_routine(table))
		return (false);
	if (!wait_philosophers_finish_their_dinner(table))
		return (false);
	// pthread_mutex_unlock(&table->write_to_sign_of_death);
	return (true);
}
