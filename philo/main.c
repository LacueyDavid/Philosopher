/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:35:14 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/13 15:35:38 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (!check_arguments_validity(argc, argv))
		return (1);
	if (!prepare_the_table(&table, argc, argv))
		return (1);
	if (!start_the_dinner(&table))
		return (1);
	clean_the_table(&table);
	return (0);
}
