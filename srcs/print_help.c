#include "ft_traceroute.h"

void print_help(void)
{
	ft_putstr_fd("Usage: ft_traceroute [-h] destination\n-h print help", 2);
	exit(EXIT_FAILURE);
}
