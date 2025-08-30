#include "../philo.h"

bool	eat(t_philo *philo)
{
	if (check_death(philo->data))
		return (false);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal_time = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_printf("%ld %ld is eating\n", philo->id, philo->data);
	ft_usleep(philo->data->time_to_eat);
	release_forks(philo);
	return (true);
}

bool	_sleep(t_philo *philo)
{
	if (check_death(philo->data))
		return (false);
	ft_printf("%ld %ld is sleeping\n", philo->id, philo->data);
	ft_usleep(philo->data->time_to_sleep);
	return (true);
}

bool	think(t_philo *philo)
{
	if (check_death(philo->data))
		return (false);
	ft_printf("%ld %ld is thinking\n", philo->id, philo->data);
	return (true);
}

bool	start_cycle(t_philo *philo)
{
	if (!take_forks(philo) || !eat(philo) || !_sleep(philo) || !think(philo))
		return (false);
	return (true);
}
