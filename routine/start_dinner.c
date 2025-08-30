#include "../philo.h"

bool	create_threads(t_data *data)
{
	int		i;
	t_philo *philos;

	i = 0;
	philos = data->philos;
	while (i < data->philos_count)
	{
		if (pthread_create(&philos[i].thread_id, NULL, philo_routine,
					 &philos[i]))
			return (false);
		i++;
	}
	if (data->philos_count &&
		pthread_create(&data->monitor, NULL, monitor_routine, data))
		return (false);
	return (true);
}

bool	join_threads(t_data *data)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = data->philos;
	while (i < data->philos_count)
	{
		if (pthread_join(philos[i].thread_id, NULL))
			return (false);
		i++;
	}
	if (pthread_join(data->monitor, NULL))
		return (false);
	return (true);
}

bool start_dinner(t_data *data)
{
	printf("data from start dinner: %p\n", &data);

	if (!create_threads(data))
		return (false);
	if (!join_threads(data))
		return (false);
	return (true);
}