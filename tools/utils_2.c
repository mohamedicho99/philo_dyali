/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:22:28 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/08/30 21:22:33 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_printf(char *s, long philo_id, t_data *data)
{
	bool	death;

	pthread_mutex_lock(&data->mutex_death);
	death = data->death;
	pthread_mutex_unlock(&data->mutex_death);
	pthread_mutex_lock(&data->mutex_print);
	if (!death)
		printf(s, get_current_time(data), philo_id);
	pthread_mutex_unlock(&data->mutex_print);
}

void	init_evens_turn(t_data *data)
{
	pthread_mutex_lock(&data->mutex_turn);
	data->turn = EVEN;
	pthread_mutex_unlock(&data->mutex_turn);
}

void	declare_creation(t_data *data)
{
	pthread_mutex_lock(&data->mutex_monitor_ready);
	data->start_time = get_time_ms();
	data->monitor_ready = true;
	pthread_mutex_unlock(&data->mutex_monitor_ready);
}

void	switch_turn(t_data *data)
{
	pthread_mutex_lock(&data->mutex_turn);
	data->turn = !data->turn;
	pthread_mutex_unlock(&data->mutex_turn);
}
