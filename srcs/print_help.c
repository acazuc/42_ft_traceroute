#include "ft_traceroute.h"

void print_help(void)
{
	ft_putstr_fd("Usage: ft_traceroute [-h max_hops] destination\n", 2);
	exit(EXIT_FAILURE);
}
