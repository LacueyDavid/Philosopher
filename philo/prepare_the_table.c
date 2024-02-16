/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_the_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:30:06 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/16 16:15:51 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	table_take_the_timers(t_table *table, int argc, char **argv)
{
	table->dinner_start_time = get_time_in_ms();
	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		table->times_each_philosopher_must_eat = -1;
}

static bool	put_the_forks_on_the_table(t_table *table)
{
	size_t	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_mutex_init(&table->forks[index], NULL) != 0)
		{
			printf("Error: mutex init failed\n");
			clean_the_forks(table, index);
			return (false);
		}
		index++;
	}
	return (true);
}

static bool	table_prepare_the_right_to_write(t_table *table)
{
	if (pthread_mutex_init(&table->right_to_write, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		return (false);
	}
	if (pthread_mutex_init(&table->write_to_sign_of_death, NULL) != 0)
	{
		printf("Error: mutex init failed\n");
		pthread_mutex_destroy(&table->right_to_write);
		return (false);
	}
	table->sign_of_death = false;
	return (true);
}

bool	prepare_the_table(t_table *table, int argc, char **argv)
{
	table_take_the_timers(table, argc, argv);
	if (!table_prepare_the_right_to_write(table))
		return (false);
	if (!put_the_forks_on_the_table(table))
		return (false);
	if (!philos_take_their_seats(table))
	{
		clean_the_forks(table, table->number_of_philosophers);
		return (false);
	}
	return (true);
}
