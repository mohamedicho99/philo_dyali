#include "../philo.h"

long	get_timestamp(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long ms)
{
	long start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}

void	ft_bzero(void *s, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char*)s;
	while (i < len)
	{
		ptr[i] = '\0';
		i++;
	}
}

void	*ft_calloc(int size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
