/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_the_dinner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:50:38 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/16 16:53:42 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_philos_die(t_table *table)
{
	size_t	index;
	size_t	time;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		time = get_time_in_ms();
		if (time - table->philos[index].last_meal_time > table->time_to_die)
		{
			pthread_mutex_lock(&table->write_to_sign_of_death);
			table->sign_of_death = table->philos[index].id;
			pthread_mutex_unlock(&table->write_to_sign_of_death);
			break ;
		}
		index++;
	}
	return ;
}

static void	check_philos_reach_max_meals(t_table *table)
{
	size_t	index;
	int		everyone_eat;

	index = 0;
	everyone_eat = 1;
	while (index < table->number_of_philosophers)
	{
		pthread_mutex_lock(&table->philos[index].number_of_meals_mutex);
		if ((int)table->philos[index].number_of_meals < table->times_each_philosopher_must_eat)
			everyone_eat = 0;
		pthread_mutex_unlock(&table->philos[index].number_of_meals_mutex);
		index++;
	}
	if (everyone_eat)
	{
		pthread_mutex_lock(&table->write_to_sign_of_death);
		table->sign_of_death = -1;
		pthread_mutex_unlock(&table->write_to_sign_of_death);
	}
	return ;
}

void *print_dead(void *arg)
{
	t_table *table;
	size_t	time;

	table = (t_table *)arg;
	while(true)
	{
		check_philos_die(table);
		if (table->times_each_philosopher_must_eat > 0)
			check_philos_reach_max_meals(table);
		time = get_time_in_ms() - table->dinner_start_time;
		pthread_mutex_lock(&table->write_to_sign_of_death);
		if (table->sign_of_death > 0)
		{
			printf("%ld %d %s\n", time, table->sign_of_death, "died");
			pthread_mutex_unlock(&table->write_to_sign_of_death);
			break;
		}
		else if (table->sign_of_death == -1)
		{
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
	return (true);
}
