#include "../philo.h"

bool	take_fork(t_philo *philo, t_fork *fork)
{
	if (!fork)
		return (false);
	while (!check_death(philo->data))
	{
		pthread_mutex_lock(&fork->mutex);
		if (!fork->taken)
		{
			fork->taken = true;
			pthread_mutex_unlock(&fork->mutex);
			ft_printf("%ld %ld has taken a fork\n", philo->id, philo->data);
			return (true);
		}
		pthread_mutex_unlock(&fork->mutex);
		usleep(100);
	}
	return (false);
}

bool	take_forks(t_philo *philo)
{
	if (philo->data->philos_count % 2 && philo->id == 1)
		usleep(1000);
	if (!take_fork(philo, philo->right_fork) || !take_fork(philo,
														philo->left_fork))
		return (false);
	return (true);
}

void	increase_eaters(t_data *data)
{
	pthread_mutex_lock(&data->mutex_eaters);
	data->eaters++;
	pthread_mutex_unlock(&data->mutex_eaters);
}

void	release_forks(t_philo *philo)
{
	increase_eaters(philo->data);
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->taken	= false;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->taken	= false;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->mutex_ate);
	philo->ate= true;
	pthread_mutex_unlock(&philo->mutex_ate);
}
