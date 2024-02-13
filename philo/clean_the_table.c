/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_the_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:38:28 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/13 15:38:29 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	clean_the_rights(t_table *table)
{
	pthread_mutex_destroy(&table->right_to_write);
	pthread_mutex_destroy(&table->write_to_sign_of_death);
}

void	clean_the_table(t_table *table)
{
	int	index;

	index = 0;
	clean_the_forks(table, table->number_of_philosophers);
	clean_the_rights(table);
}
