/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:10:45 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/08/30 21:10:51 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (parse_args(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_extra_data(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!start_dinner(&data))
		return (EXIT_FAILURE);
	clean_data(&data);
	free(data.philos);
	return (0);
}
