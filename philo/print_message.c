#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->dinner_start_time,
		philo->id, message);
}
