/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:36:41 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/16 19:46:30 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_message(t_philo *philo, char *message)
{
	size_t	time;

	time = get_time_in_ms() - philo->table->dinner_start_time;
	pthread_mutex_lock(&philo->table->write_to_sign_of_death);
	if (philo->table->sign_of_death)
	{
		pthread_mutex_unlock(&philo->table->write_to_sign_of_death);
		return (true);
	}
	printf("%ld %ld %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->table->write_to_sign_of_death);
	return (false);
}
