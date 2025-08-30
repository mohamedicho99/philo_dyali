#include "../philo.h"

void clean_data(t_data *data)
{
	if (data->philos)
	{
		free(data->philos);
		data->philos = NULL;
	}
	if (data->forks)
	{
		free(data->forks);
		data->forks = NULL;
	}
	pthread_mutex_destroy(&data->mutex_monitor_ready);
	pthread_mutex_destroy(&data->mutex_turn);
	pthread_mutex_destroy(&data->mutex_death);
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_eaters);
	data = NULL;
}