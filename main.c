#include "philo.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	t_data	data;

	// make iniit extra 
	// 	-> inits the forks data and philos data
	// make start dinner
	// 	-> create threads 
	// 		calling pthread create with philo routine
	// 			make that philo routine just print something simple for now
	// 		calling pthread create with monitor rountine 
	// 			make that monitor routine just print something simple for now
	// 	-> join thread
	// 		join philos one by one
	// 		join data->monitor

	ft_bzero(&data, sizeof(t_data));

	if (parse_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);

	if (init_extra_data(&data) == EXIT_FAILURE)
		return (0);

	if (!start_dinner(&data))
		return (EXIT_FAILURE);


	clean_data(&data);
	free(data.philos);
	return (0);
}
