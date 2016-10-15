#include "ft_traceroute.h"

int main(int ac, char **av)
{
	t_env env;

	if (getuid() != 0)
	{
		ft_putendl_fd("You're not root, please use sudo or log as root", 2);
		exit(EXIT_FAILURE);
	}
	env_init(&env);
	parse_params(&env, ac, av);
	resolve_destination(&env);
	do_connect(&env);
	ft_putstr("traceroute to ");
	ft_putstr(env.destination);
	ft_putstr(" (");
	ft_putstr(env.ip);
	ft_putstr("), 30 hops max, 60 byte packets\n");
	route(&env);
	return (EXIT_SUCCESS);
}
