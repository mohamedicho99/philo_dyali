/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:11:26 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/08/30 21:11:29 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_overflow(t_data *data, int argc)
{
	if (data->philos_count < 0)
		return (1);
	if (data->time_to_die < 0)
		return (1);
	if (data->time_to_eat < 0)
		return (1);
	if (data->time_to_sleep < 0)
		return (1);
	if (argc == 6 && data->cycle_count < 0)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	data->philos_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->cycle_count = atoi(argv[5]);
	else
		data->cycle_count = -1;
	if (check_overflow(data, argc))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *s)
{
	long	res;
	int		sign;

	while ((*s >= '\t' && *s <= '\r') || *s == ' ')
		s++;
	sign = (*s != '-') - (*s == '-');
	s += (*s == '-' || *s == '+');
	res = 0;
	while (*s >= '0' && *s <= '9')
	{
		if (res > (LONG_MAX - (*s - '0')) / 10)
			return (-sign * (sign == 1));
		res = (res * 10) + (*s - '0');
		s++;
	}
	if (*s != '\0' && !ft_isdigit(*s))
		return (-1);
	return ((int)res * sign);
}
