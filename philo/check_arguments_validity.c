/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments_validity.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:54:40 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/16 15:24:30 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_max_philo_number(char *argument)
{
	int	max_philo_number;

	max_philo_number = ft_atoi(argument);
	if (max_philo_number > 200)
	{
		printf("Error: number of philosophers must be maximum 200\n");
		return (false);
	}
	return (true);
}

bool	bigger_nbr(char *nbr, char *max)
{
	size_t	index;

	index = 0;
	if (ft_strlen(nbr) > ft_strlen(max))
		return (1);
	if (ft_strlen(nbr) < ft_strlen(max))
		return (0);
	while (nbr[index] && max[index])
	{
		if (nbr[index] > max[index])
			return (1);
		index++;
	}
	return (0);
}

bool	smaller_nbr(char *nbr, char *min)
{
	size_t	index;

	index = 0;
	nbr++;
	min++;
	if (ft_strlen(nbr) > ft_strlen(min))
		return (1);
	if (ft_strlen(nbr) < ft_strlen(min))
		return (0);
	while (nbr[index] && min[index])
	{
		if (nbr[index] > min[index])
			return (1);
		index++;
	}
	return (0);
}

bool	between_max_min(char *nbr)
{
	if (nbr[0] == '-')
		return (smaller_nbr(nbr, "-2147483648"));
	return (bigger_nbr(nbr,       "2147483647"));
}

static bool	check_argument_value(char *argument, int index)
{
	int	i;

	i = 0;
	while (argument[i])
	{
		if (!ft_isdigit(argument[i]))
		{
			printf("Error: argument %d is not a positive number\n", index);
			return (false);
		}
		if (between_max_min(argument) == 1)
		{
			printf("Error: argument %d is too big\n", index);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_arguments_values(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_argument_value(argv[i], i))
			return (false);
		i++;
	}
	return (true);
}

bool	check_arguments_validity(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: wrong number of arguments\n");
		return (false);
	}
	if (!check_arguments_values(argc, argv))
		return (false);
	if (!check_max_philo_number(argv[1]))
		return (false);
	return (true);
}
