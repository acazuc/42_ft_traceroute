#include "ft_traceroute.h"

void do_connect(t_env *env)
{
	int val;

	if ((env->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
	{
		ft_putendl_fd("ft_traceroute: Can't create socket", 2);
		exit(EXIT_FAILURE);
	}
	val = 1;
	if (setsockopt(env->socket, IPPROTO_IP, IP_HDRINCL, &val, sizeof(val)) == -1)
	{
		ft_putendl_fd("ft_traceroute: Can't setsocketop(IP_HDRINCL)", 2);
		exit(EXIT_FAILURE);
	}
}
