#include "philo.h"

static bool	philosophers_start_their_routine(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		if (pthread_create(&table->philos[index].thread, NULL,
				&philosophers_routine, &table->philos[index]) != 0)
		{
			clean_the_forks(table, table->number_of_philosophers);
			kill_every_philosophers(table, index);
			return (false);
		}
		index++;
	}
	return (true);
}

static bool	wait_philosophers_finish_their_dinner(t_table *table)
{
	int	index;

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
	return (true);
}

bool	start_the_dinner(t_table *table)
{
	if (table->number_of_philosophers == 1)
	{
		ft_usleep(table->time_to_die);
		print_message(&table->philos[0], "is dead.");
		return (true);
	}
	if (!philosophers_start_their_routine(table))
		return (false);
	if (!wait_philosophers_finish_their_dinner(table))
		return (false);
	return (true);
}
