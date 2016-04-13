#include "ft_traceroute.h"

void resolve_destination(t_env *env)
{
	struct addrinfo *res;
	struct addrinfo hints;
	char tmp[16];

	ft_bzero(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	if (getaddrinfo(env->destination, NULL, &hints, &res))
	{
		ft_putstr_fd("ft_traceroute: unknown host ", 2);
		ft_putendl_fd(env->destination, 2);
		exit(EXIT_FAILURE);
	}
	if (!res)
	{
		ft_putstr_fd("ft_traceroute: unknown host: ", 2);
		ft_putendl_fd(env->destination, 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(tmp, 16);
	if (!inet_ntop(AF_INET, &((struct sockaddr_in*)res->ai_addr)->sin_addr, tmp, 16))
	{
		ft_putstr_fd("ft_traceroute: unknown host ", 2);
		ft_putendl_fd(env->destination, 2);
		exit(EXIT_FAILURE);
	}
	env->ip = ft_strdup(tmp);
	env->addrlen = res->ai_addrlen;
	if (!(env->addr = malloc(res->ai_addrlen)))
	{
		ft_putstr_fd("ft_traceroute: can't malloc addr\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_memcpy(env->addr, res->ai_addr, res->ai_addrlen);
}
