/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_extra_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:18:40 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/08/30 21:18:41 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

t_fork	*init_forks_data(t_data *data)
{
	int		i;
	t_fork	*forks;

	forks = ft_calloc(sizeof(t_fork) * data->philos_count);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < data->philos_count)
	{
		forks[i].id = i;
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
	return (forks);
}

t_philo	*init_philos_data(t_data *data)
{
	t_philo	*philos;
	int		i;
	int		count;

	count = data->philos_count;
	philos = ft_calloc(sizeof(t_philo) * count);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < count)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].right_fork = &data->forks[(i + 1) % count];
		if (count > 1)
			philos[i].left_fork = &data->forks[i];
		philos[i].cycles = data->cycle_count;
		pthread_mutex_init(&philos[i].mutex_last_meal, NULL);
		pthread_mutex_init(&philos[i].mutex_ate, NULL);
		pthread_mutex_init(&philos[i].mutex_full, NULL);
		i++;
	}
	return (philos);
}

int	init_extra_data(t_data *data)
{
	data->forks = init_forks_data(data);
	if (!data->forks)
		return (EXIT_FAILURE);
	data->philos = init_philos_data(data);
	if (!data->philos)
		return (EXIT_FAILURE);
	pthread_mutex_init(&data->mutex_monitor_ready, NULL);
	pthread_mutex_init(&data->mutex_death, NULL);
	pthread_mutex_init(&data->mutex_eaters, NULL);
	pthread_mutex_init(&data->mutex_turn, NULL);
	pthread_mutex_init(&data->mutex_print, NULL);
	return (EXIT_SUCCESS);
}
