/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlacuey <dlacuey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:54:27 by dlacuey           #+#    #+#             */
/*   Updated: 2024/02/16 15:25:24 by dlacuey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

static int	skip_space(const char *nptr)
{
	int	index;

	index = 0;
	while ((nptr[index] >= '\t' && nptr[index] <= '\r') || nptr[index] == ' ')
		index++;
	return (index);
}

static int	get_sign(const char *nptr, int index)
{
	if (nptr[index] == '-')
		return (-1);
	else if (nptr[index] == '+')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	number;
	int	index;
	int	sign;

	number = 0;
	index = skip_space(nptr);
	sign = get_sign(nptr, index);
	if (sign)
		index++;
	else
		sign = 1;
	while (nptr[index])
	{
		if (nptr[index] < '0' || nptr[index] > '9')
			return (number * sign);
		number = number * 10 + nptr[index] - '0';
		index++;
	}
	return (number * sign);
}

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
