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
	int	index;

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

void	assign_forks_to_philo(t_philo *philo, int number_of_philos,
				pthread_mutex_t *forks)
{
	int	index;

	index = 0;
	while (index < number_of_philos)
	{
		philo[index].left_fork = &forks[index];
		if (index == 0)
			philo[index].right_fork = &forks[number_of_philos - 1];
		else
			philo[index].right_fork = &forks[index - 1];
		index++;
	}
}

void	assign_id_to_philo(t_philo *philo, int number_of_philosophers)
{
	int index;

	index = 0;
	while (index < number_of_philosophers)
	{
		philo[index].id = index + 1;
		index++;
	}
}

void	assign_table_to_philo(t_table *table)
{
	int	index;

	index = 0;
	while (index < table->number_of_philosophers)
	{
		table->philos[index].table = table;
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

bool	prepare_the_table(t_table *table, int argc, char **argv)
{
	table_take_the_timers(table, argc, argv);
	if (!put_the_forks_on_the_table(table))
		return (false);
	philos_take_their_seats(table);
	return (true);
}
