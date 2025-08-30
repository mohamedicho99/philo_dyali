#include "../philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			result;
	
	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

long get_current_time(t_data *data)
{
	return (get_time_ms() - data->start_time);
}

bool	check_death(t_data *data)
{
	bool	death;

	pthread_mutex_lock(&data->mutex_death);
	death = data->death;
	pthread_mutex_unlock(&data->mutex_death);
	if (death)
		return (true);
	return (false);
}