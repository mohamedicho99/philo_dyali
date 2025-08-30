#include "../philo.h"

long get_time_ms(void)
{
	struct timeval	tv;
	long			result;
	
	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}