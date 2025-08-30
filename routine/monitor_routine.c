#include "../philo.h"

void *monitor_routine(void *arg)
{
	t_data *data;

	data = (t_data *)arg;

	init_evens_turn(data);
	declare_creation(data);

	printf("data from monitor routine %p \n", &data);
	
	return (NULL);
}