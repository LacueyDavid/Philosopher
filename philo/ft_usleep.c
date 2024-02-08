#include "philo.h"

void	ft_usleep(size_t time_in_ms)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time_in_ms)
		usleep(100);
}
