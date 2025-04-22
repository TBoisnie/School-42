#ifndef FT_PING_H
#define FT_PING_H

#include <netdb.h>
#include <netinet/ip.h>
#include <sys/time.h>
#include <netinet/ip_icmp.h>

#include "libft/incs/libft.h"

// =============================================================================
// Preprocessor
// =============================================================================
// Define ----------------------------------------------------------------------
#define USAGE \
	"\nUsage\n" \
	"\tft_ping [options...] <destination...>\n\n" \
	"Parameters:\n" \
	"\t<destination>\t\tdns name or ip address\n" \
	"Options:\n" \
	"\t-d\t\t\tuse SO_DEBUG socket option\n" \
	"\t-f\t\t\tflood ping\n" \
	"\t-h,-?\t\t\tprint help and exit\n" \
	"\t-n\t\t\tdo not resolve host addresses\n" \
	"\t-q\t\t\tquiet output\n" \
	"\t-r\t\t\tuse SO_DONTROUTE socket option\n" \
	"\t-v\t\t\tverbose output\n" \
	"\t--count=<count>\t\tstop after sending <count> packets\n" \
	"\t--interval=<interval>\twait <interval> seconds between sending each packet\n" \
	"\t--linger=<linger>\tnumber of seconds to wait for response\n" \
	"\t--pattern=<pattern>\tfill ICMP packet with given <pattern> (hex)\n" \
	"\t--preload=<preload>\tsend <preload> packets as fast as possible before falling into normal mode of behavior\n" \
	"\t--size=<size>\t\tsend <size> data octets\n" \
	"\t--timeout=<timeout>\tstop after <timeout> seconds\n" \
	"\t--tos=<tos>\t\tspecify <tos> as type of service\n" \
	"\t--ttl=<ttl>\t\tspecify <ttl> as time-to-live\n"

#define OPT_FLOOD       (1u << 0)
#define OPT_INTERVAL    (1u << 1)
#define OPT_NUMERIC     (1u << 2)
#define OPT_QUIET       (1u << 3)
#define OPT_VERBOSE     (1u << 4)
#define OPT_DEBUG       (1u << 5)
#define OPT_DONTROUTE   (1u << 6)
#define OPT_PATTERN     (1u << 7)
#define OPT_COUNT       (1u << 8)
#define OPT_SIZE        (1u << 9)
#define OPT_TOS         (1u << 10)
#define OPT_TTL         (1u << 11)
#define OPT_LINGER      (1u << 12)
#define OPT_PRELOAD     (1u << 13)
#define OPT_TIMEOUT     (1u << 14)

#define HOST_TAB_SIZE     32
#define PATTERN_TAB_SIZE  16
#define ACK_TAB_SIZE      128

#define DEFAULT_PRELOAD      0
#define DEFAULT_COUNT        0
#define DEFAULT_TIMEOUT      0
#define DEFAULT_INTERVAL     1
#define DEFAULT_TTL          64
#define DEFAULT_TOS          -1
#define DEFAULT_LINGER       10
#define DEFAULT_SIZE         (64 - ICMP_MINLEN)
#define DEFAULT_PATTERN      "0123456789ABCDEF"
#define DEFAULT_PATTERN_SIZE (sizeof(DEFAULT_PATTERN) - 1)

#define IP_HDR_SIZE_MAX    60
#define ICMP_HDR_SIZE_MAX  76
#define PACKET_SIZE_MAX    65535
#define DATA_SIZE_MAX      (PACKET_SIZE_MAX - IP_HDR_SIZE_MAX - ICMP_HDR_SIZE_MAX)

// Macro -----------------------------------------------------------------------
#define IS_TIMEABLE(s)  ((s) >= sizeof(struct timeval))

#define ACK_BYTE(id)   (_ctx->stats.ack[(id) >> 3])
#define ACK_MASK(id)   (1 << ((id) & 0x07))
#define ACK_INDEX(id)  ((id) % (8 * ACK_TAB_SIZE))

#define PING_ACK_SET(id) \
	FT_MEM_BIT_SET(ACK_BYTE(ACK_INDEX(id)), ACK_MASK(ACK_INDEX(id)))

#define PING_ACK_UNSET(id) \
	FT_MEM_BIT_UNSET(ACK_BYTE(ACK_INDEX(id)), ACK_MASK(ACK_INDEX(id)))

#define PING_ACK_ISSET(id) \
	FT_MEM_BIT_ISSET(ACK_BYTE(ACK_INDEX(id)), ACK_MASK(ACK_INDEX(id)))

// =============================================================================
// Type
// =============================================================================
// Typedef ---------------------------------------------------------------------
typedef struct s_ctx      t_ctx;
typedef struct s_options  t_options;
typedef struct s_stats    t_stats;

// Enum ------------------------------------------------------------------------
// Union -----------------------------------------------------------------------
// Struct ----------------------------------------------------------------------
struct s_stats
{
	t_size transmitted;
	t_size received;
	t_size duplicated;
	t_size failed;

	t_byte ack[ACK_TAB_SIZE];

	t_double time_min;
	t_double time_max;
	t_double time_total;
	t_double time_total_squared;
};

struct s_options
{
	t_int_32 preload;
	t_int_32 count;
	t_int_32 size;
	struct {
		t_byte data[PATTERN_TAB_SIZE];
		t_uint_8 length;
	} pattern;
	t_int_32 interval;
	t_int_32 linger;
	t_int_32 timeout;
	t_int_32 tos;
	t_int_32 ttl;

	t_uint_32 flags;
	t_char const * hosts[HOST_TAB_SIZE + 1];
};

struct s_ctx
{
	t_fd socket;
	t_pid identifier;

	struct timeval started_at;

	t_char dst_name[NI_MAXHOST];
	struct sockaddr_in dst_addr;

	t_byte packet[PACKET_SIZE_MAX];

	t_options options;
	t_stats stats;
};

// Function --------------------------------------------------------------------

#endif
