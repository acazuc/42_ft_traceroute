#include "ft_traceroute.h"

int read_options(t_env *env, int ac, char **av)
{
  int tmp = 255;
  if (ac > 1) {
    if (!ft_strcmp(av[1], "-h")) {
      if (ac < 2 || !ft_strisdigit(av[2])) {
        print_help();
      }
      while (av[2][0] == '0') {
        av[2]++;
      }
      if (ft_strlen(av[2]) > 3 || (tmp = ft_atoi(av[2])) > 255) {
        print_help();
      }
      env->hops = (unsigned char)tmp;
      return (3);
    }
  }
  return (1);
}

void parse_params(t_env *env, int ac, char **av)
{
  int count;

  count = read_options(env, ac, av);
  if (count != ac - 1) {
    print_help();
  }
  env->destination = av[count];
}
