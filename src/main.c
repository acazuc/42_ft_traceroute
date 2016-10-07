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
  route(&env);
}
