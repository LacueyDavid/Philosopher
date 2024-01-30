#include "philo.h"

void	clean_the_forks(t_table *table, int size_to_clear)
{
	int	index;

	index = 0;
	while (index < size_to_clear)
	{
		pthread_mutex_destroy(&table->forks[index]);
		index++;
	}
}

void	kill_every_philosophers(t_table *table, int size_to_clear)
{
	int	index;

	index = 0;
	while (index < size_to_clear)
	{
		pthread_detach(table->philos[index].thread);
		index++;
	}
}

void	clean_the_table(t_table *table)
{
	int	index;

	index = 0;
	clean_the_forks(table, table->number_of_philosophers);
	kill_every_philosophers(table, table->number_of_philosophers);
}
