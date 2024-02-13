/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:36:21 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/13 15:36:31 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t time_in_ms)
{
	size_t	start_time;

	start_time = get_time_in_ms();
	while (get_time_in_ms() - start_time < time_in_ms)
		usleep(100);
}
