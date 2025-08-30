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

void init_evens_turn(t_data *data)
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