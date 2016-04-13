#include "ft_traceroute.h"

static void build_ip_header(t_env *env, struct iphdr *header)
{
	ft_bzero(header, sizeof(*header));
	header->version = 4;
	header->ihl = 5;
	header->tos = 0;
	header->tot_len = sizeof(t_packet);
	header->id = ICMP_ECHO;
	header->frag_off = 0;
	header->ttl = env->count;
	header->protocol = IPPROTO_ICMP;
	header->check = 0;
	if (inet_pton(AF_INET, env->ip, &header->daddr) != 1)
	{
		ft_putendl_fd("ft_traceroute: can't pton ip", 2);
		exit(EXIT_FAILURE);
	}
	header->saddr = 0;
	header->check = 0;
}

static void build_icmp_header(t_env *env, struct icmphdr *header)
{
	ft_bzero(header, sizeof(*header));
	header->type = ICMP_ECHO;
	header->code = 0;
	header->un.echo.id = getpid();
	header->un.echo.sequence = (uint16_t)env->pcount;
	header->checksum = 0;
	header->checksum = ip_checksum(header, sizeof(t_packet) - sizeof(struct iphdr));
}

static int run_packet(t_env *env)
{
	t_packet packet;
  long send;
  long recv;
  char ip[16];

  while (1)
  {
    env->pcount++;
    ft_bzero(&packet.data, sizeof(packet.data));
    ft_memcpy(&(packet.data[0]), &env->pcount, sizeof(env->pcount));
  	build_ip_header(env, &packet.ip_header);
  	build_icmp_header(env, &packet.icmp_header);
  	if (sendto(env->socket, &packet, sizeof(packet), MSG_CONFIRM, env->addr, env->addrlen) == -1)
    {
  	   continue;
    }
    send = epoch_micro();
    int i = 0;
    while (i < 1) {
      ft_bzero(&packet, sizeof(packet));
      if (recvfrom(env->socket, &packet, sizeof(packet), 0, env->addr, (socklen_t*)&env->addrlen) == -1)
    	{
        i++;
        continue;
      }
      recv = epoch_micro();
      if (packet.icmp_header.type != 11 && packet.icmp_header.type != 0)
      {
        continue;
      }
			if (packet.icmp_header.type == 0 && (packet.icmp_header.un.echo.sequence != env->pcount || packet.icmp_header.un.echo.id != getpid()))
			{
				continue;
			}
      printf("%2d. %-15s %.1f ms\n", env->count, inet_ntop(AF_INET, &packet.ip_header.saddr, ip, 16), (recv - send) / 1000.);
      if (packet.icmp_header.type == 0)
      {
        return (1);
      }
      return (0);
    }
  }
  return (0);
}

void route(t_env *env)
{
  int finished;
  struct timeval tv;

  finished = 0;
  tv.tv_sec = 1;
  tv.tv_usec = 0;
  if (setsockopt(env->socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
  {
      ft_putendl_fd("ft_traceroute: can't sockopt receive_timeout", 2);
  }
  if (setsockopt(env->socket, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0)
  {
      ft_putendl_fd("ft_traceroute: can't sockopt send_timeout", 2);
  }
  while (!finished)
  {
    env->count++;
    if (run_packet(env))
    {
      finished = 1;
    }
  }
}
