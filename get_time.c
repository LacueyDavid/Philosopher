#include "philo.h"

size_t	get_time_in_ms()
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error: gettimeofday() failed\n");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
