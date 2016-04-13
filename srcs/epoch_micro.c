#include "ft_traceroute.h"

size_t epoch_micro(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
	{
		ft_putendl_fd("ft_traceroute: can't get time, aborting", 2);
		exit(EXIT_FAILURE);
	}
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
