#include "../philo.h"

void wait_for_monitor_creation(t_data *data)
{
	// this is the function that keeps the other threads waiting until 
	// the monitor is starting to do its job!
	// the thing is this function runs forever but we use usleep 100
	// before retrying to check if the monitor is ready yet
	// and we add that sleep just not to exost the cpu
	while (true)
	{
		pthread_mutex_lock(&data->mutex_monitor_ready);
		if (data->monitor_ready == true)
		{
			pthread_mutex_unlock(&data->mutex_monitor_ready);
			break;
		}
		pthread_mutex_unlock(&data->mutex_monitor_ready);
		usleep(100);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	wait_for_monitor_creation(philo->data);
	printf("philosopher %ld is alive\n", philo->id);
	return (NULL);
}