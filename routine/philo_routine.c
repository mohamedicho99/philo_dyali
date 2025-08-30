#include "../philo.h"

void wait_for_monitor_creation(t_data *data)
{
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

t_type	philo_turn(t_data *data)
{
	t_type	turn;

	pthread_mutex_lock(&data->mutex_turn);
	turn = data->turn;
	pthread_mutex_unlock(&data->mutex_turn);
	return turn;
}

bool	ate_once(t_philo *philo)
{
	bool	ate;

	pthread_mutex_lock(&philo->mutex_ate);
	ate = philo->ate;
	pthread_mutex_unlock(&philo->mutex_ate);
	if (ate)
		return (true);
	return (false);
}

bool	check_turn(t_philo *philo)
{
	while (!check_death(philo->data))
	{
		if (philo->id % 2 == philo_turn(philo->data) && !ate_once(philo))
			return (true);
		usleep(100);
	}
	return (false);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	wait_for_monitor_creation(philo->data);

	while (philo->cycles == -1 || philo->cycles > 0)
	{
		if (!check_turn(philo))
			return (NULL);
		if (!start_cycle(philo))
			return (NULL);
		if (philo->cycles != -1)
			philo->cycles--;
		printf("ok\n");
	}

	pthread_mutex_lock(&philo->data->mutex_full);
	philo->full = true;
	pthread_mutex_unlock(&philo->data->mutex_full);
	return (NULL);
}