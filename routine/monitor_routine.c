#include "../philo.h"

void	reset_ate_bool(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->philos_count)
	{
		pthread_mutex_lock(&data->philos[i].mutex_ate);
		data->philos[i].ate = false;
		pthread_mutex_unlock(&data->philos[i].mutex_ate);
		i++;
	}
}

void	check_fork_release(t_data *data)
{
	t_type	mode;
	long	num;

	pthread_mutex_lock(&data->mutex_turn);
	mode = data->turn;
	pthread_mutex_unlock(&data->mutex_turn);
	if (mode == EVEN)
		num = data->philos_count / 2; 
	else
		num = (data->philos_count + 1) / 2;
	pthread_mutex_lock(&data->mutex_eaters);
	if (data->eaters == num)
	{
		data->eaters = 0;
		switch_turn(data);
		reset_ate_bool(data);
	}
	pthread_mutex_unlock(&data->mutex_eaters);
}

bool	check_fullness(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = data->philos;
	while (i < data->philos_count)
	{
		pthread_mutex_lock(&philos[i].mutex_full);
		if (!philos[i].full)
		{
			pthread_mutex_unlock(&philos[i].mutex_full);
			return (false);
		}
		pthread_mutex_unlock(&philos[i].mutex_full);
		i++;
	}

	return (true);
}

bool	check_starvation(t_philo *philo)
{
	long	time_to_die;
	long	last_meal;
	bool	full;

	pthread_mutex_lock(&philo->mutex_full);
	full = philo->full;
	pthread_mutex_unlock(&philo->mutex_full);
	if (full)
		return (false);
	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->mutex_last_meal);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mutex_last_meal);
	if (get_current_time(philo->data) - last_meal > time_to_die)
	{
		pthread_mutex_lock(&philo->data->mutex_death);
		philo->data->death = true;
		pthread_mutex_unlock(&philo->data->mutex_death);
		ft_usleep(1);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %ld died\n", get_current_time(philo->data), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	return (true);
}

void *monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;

	init_evens_turn(data);
	declare_creation(data);


	// start an infinit loop
	while (true)
	{
		check_fork_release(data);
		i = 0;
		while (i < data->philos_count)
		{
			if (check_fullness(data) || check_starvation(&data->philos[i]))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}