#include "philo.h"

// ////////////////////////// test we dont care about /////////////////////////////
//
// static bool	is_philos_alive(t_philo *philos, int number_of_philosophers)
// {
// 	int	index;
//
// 	index = 0;
// 	while (index < number_of_philosophers)
// 	{
// 		printf("Philosopher %d is alive\n", philos[index].id);
// 		index++;
// 	}
// 	return (true);
// }
//
// static bool	philo_tests(t_table *table)
// {
// 	printf("Number of philosophers: %d\n", table->number_of_philosophers);
// 	printf("Time to die: %d\n", table->time_to_die);
// 	printf("Time to eat: %d\n", table->time_to_eat);
// 	printf("Time to sleep: %d\n", table->time_to_sleep);
// 	printf("Times each philosopher must eat: %d\n",
// 		table->times_each_philosopher_must_eat);
// 	if (!is_philos_alive(table->philos, table->number_of_philosophers))
// 		return (false);
// 	return (true);
// }
//
// ////////////////////////////////////////////////////////////////////////////////

int		main(int argc, char **argv)
{
	t_table	table;

	if (!check_arguments_validity(argc, argv)) // check la validité des arguments
		return (1);
	if (!prepare_the_table(&table, argc, argv)) //init des mutex des forks
		return (1);
	if (!start_the_dinner(&table)) // init des threads
		return (1);
	// if (!philo_tests(&table)) // tests personnel
	// 	return (clean_the_table(&table), 1);
	clean_the_table(&table);
	return (0);
}
