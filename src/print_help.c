#include "ft_traceroute.h"

void print_help(void)
{
	ft_putstr_fd("ft_traceroute: print route of network packet from host to destination\nUsage: ft_traceroute [-h] destination\n-h print help\n", 2);
	exit(EXIT_FAILURE);
}
