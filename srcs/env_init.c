#include "ft_traceroute.h"

void env_init(t_env *env)
{
  env->hops = 255;
  env->destination = NULL;
  env->ip = NULL;
  env->count = 0;
  env->pcount = 0;
}
