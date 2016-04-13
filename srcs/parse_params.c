#include "ft_traceroute.h"

int read_options(int ac, char **av)
{
  if (ac > 1)
  {
    if (!ft_strcmp(av[1], "-h"))
    {
    	print_help();
    }
  }
  return (1);
}

void parse_params(t_env *env, int ac, char **av)
{
  int count;

  count = read_options(ac, av);
  if (count != ac - 1)
  {
    print_help();
  }
  env->destination = av[count];
}
