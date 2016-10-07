#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include "../libft/include/libft.h"
# include <sys/socket.h>
# include <netinet/in.h>
# include <linux/icmp.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <linux/ip.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <errno.h>
# include <netdb.h>
# include <math.h>

typedef struct s_env t_env;
typedef struct s_packet t_packet;

struct s_env
{
	char *destination;
	char *ip;
	int socket;
	struct sockaddr *addr;
	size_t addrlen;
	uint16_t count;
	uint16_t pcount;
};

struct s_packet
{
	struct iphdr ip_header;
	struct icmphdr icmp_header;
	char data[56];
};

void parse_params(t_env *env, int ac, char **av);
void print_help(void);
void resolve_destination(t_env *env);
void do_connect(t_env *env);
uint16_t ip_checksum(void *val, size_t len);
size_t epoch_micro(void);
void env_init(t_env *env);
void route(t_env *env);

#endif
