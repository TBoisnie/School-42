#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#include "ft_ping.h"

// =============================================================================
// Variable
// =============================================================================
// Static ----------------------------------------------------------------------
static t_bool volatile g_stop = false;

// Global ----------------------------------------------------------------------
// Extern ----------------------------------------------------------------------

// =============================================================================
// Function
// =============================================================================
// Time ------------------------------------------------------------------------
static t_void
_time_sub(
	struct timeval * _out,
	struct timeval const * _in
)
{
	if ((_out->tv_usec -= _in->tv_usec) < 0)
	{
		--_out->tv_sec;
		_out->tv_usec += 1000000;
	}

	_out->tv_sec -= _in->tv_sec;
}

// Address ---------------------------------------------------------------------
static t_char const *
_addr_to_str(
	struct in_addr const * _addr
)
{
	static t_char buffer[INET_ADDRSTRLEN];

	return (inet_ntop(AF_INET, _addr, buffer, INET_ADDRSTRLEN));
}

static t_char const *
_sockaddr_to_str(
	struct sockaddr_in const * _addr,
	t_bool _numeric_only
)
{
	// Note: Format as `hostname (ip)` or `ip` if no hostname
	static t_char buffer[INET_ADDRSTRLEN + NI_MAXHOST + 4];

	// IP
	t_char ip_str[INET_ADDRSTRLEN];

	t_int_32 error = getnameinfo((struct sockaddr *)_addr, sizeof(*_addr), ip_str, sizeof(ip_str), nullptr, 0, NI_NUMERICHOST);

	if (error)
	{
		dprintf(2, "ft_ping: getnameinfo: %s\n", (error == EAI_SYSTEM) ? strerror(errno) : gai_strerror(error));

		snprintf(buffer, sizeof(buffer), "unknown");
		return (buffer);
	}

	if (_numeric_only)
	{
		snprintf(buffer, sizeof(buffer), "%s", ip_str);
		return (buffer);
	}

	// Hostname
	t_char host_str[NI_MAXHOST];

	error = getnameinfo((struct sockaddr *)_addr, sizeof(*_addr), host_str, sizeof(host_str), nullptr, 0, NI_NAMEREQD);

	if (error)
	{
		snprintf(buffer, sizeof(buffer), "%s", ip_str);
		return (buffer);
	}

	snprintf(buffer, sizeof(buffer), "%s (%s)", host_str, ip_str);

	return (buffer);
}

// Signal ----------------------------------------------------------------------
static t_void
_signal_handler()
{
	g_stop = true;
}

// Error -----------------------------------------------------------------------
static t_void
_print_ip(
	t_ctx const * _ctx,
	struct icmp const * _icmp
)
{
	struct ip const * ip = &_icmp->icmp_ip;

	// Header
	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_VERBOSE))
	{
		printf("IP Hdr Dump:\n ");

		t_size i;
		for (i = 0; i < sizeof(struct ip); ++i)
		{
			printf("%02x%s", * ((t_byte *) ip + i), (i % 2) ? " " : "");
		}

		printf("\n");
	}

	printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
	printf(" %1x  %1x  %02x", ip->ip_v, ip->ip_hl, ip->ip_tos);
	printf(" %04x %04x", (ip->ip_len > 0x2000) ? ntohs(ip->ip_len) : ip->ip_len, ntohs(ip->ip_id));
	printf("   %1x %04x", (ntohs(ip->ip_off) & 0xe000) >> 13, ntohs(ip->ip_off) & 0x1fff);
	printf("  %02x  %02x %04x", ip->ip_ttl, ip->ip_p, ntohs(ip->ip_sum));
	printf(" %s ", _addr_to_str(&ip->ip_src));
	printf(" %s ", _addr_to_str(&ip->ip_dst));

	t_byte const * ip_opts = (t_byte *) ip + sizeof(struct ip);

	t_size i;
	for (i = sizeof(struct ip); i < (ip->ip_hl << 2); i++)
	{
		printf("%02x", *ip_opts++);
	}

	printf("\n");

	// Message
	t_byte const * p = (t_byte *) ip + (ip->ip_hl << 2);

	switch (ip->ip_p)
	{
		case IPPROTO_TCP:
		case IPPROTO_UDP:
			printf("%s: from port %u, to port %u (decimal)\n",
				(ip->ip_p == IPPROTO_TCP) ? "TCP" : "UDP",
				(*p * 256 + *(p + 1)),
				(*(p + 2) * 256 + *(p + 3))
			);
			break;
		case IPPROTO_ICMP:
		{
			t_uint_8 type = *p;
			t_uint_8 code = *(p + 1);

			printf("ICMP: type %u, code %u, size %u", type, code, ntohs(ip->ip_len) - (ip->ip_hl << 2));

			if (type == ICMP_ECHOREPLY || type == ICMP_ECHO)
			{
				printf(", id 0x%04x, seq 0x%04x", *(p + 4) * 256 + *(p + 5), *(p + 6) * 256 + *(p + 7));
			}

			printf("\n");
			break;
		}
		default:
			break;
	}
}

static t_void
_print_icmp(
	t_ctx const * _ctx,
	struct icmp const * _icmp
)
{
	typedef struct
	{
		t_uint_8 type;
		t_uint_8 code;
		t_char const * desc;
	} t_icmp_desc;

	static t_icmp_desc const icmp_desc[] =
	{
		{ ICMP_DEST_UNREACH,  ICMP_NET_UNREACH,    "Destination Net Unreachable",                 },
		{ ICMP_DEST_UNREACH,  ICMP_HOST_UNREACH,   "Destination Host Unreachable",                },
		{ ICMP_DEST_UNREACH,  ICMP_PROT_UNREACH,   "Destination Protocol Unreachable",            },
		{ ICMP_DEST_UNREACH,  ICMP_PORT_UNREACH,   "Destination Port Unreachable",                },
		{ ICMP_DEST_UNREACH,  ICMP_FRAG_NEEDED,    "Fragmentation needed and DF set",             },
		{ ICMP_DEST_UNREACH,  ICMP_SR_FAILED,      "Source Route Failed",                         },
		{ ICMP_DEST_UNREACH,  ICMP_NET_UNKNOWN,    "Network Unknown",                             },
		{ ICMP_DEST_UNREACH,  ICMP_HOST_UNKNOWN,   "Host Unknown",                                },
		{ ICMP_DEST_UNREACH,  ICMP_HOST_ISOLATED,  "Host Isolated",                               },
		{ ICMP_DEST_UNREACH,  ICMP_NET_UNR_TOS,    "Destination Network Unreachable At This TOS", },
		{ ICMP_DEST_UNREACH,  ICMP_HOST_UNR_TOS,   "Destination Host Unreachable At This TOS",    },
		#ifdef ICMP_PKT_FILTERED
		{ ICMP_DEST_UNREACH,  ICMP_PKT_FILTERED,   "Packet Filtered",                             },
		#endif
		#ifdef ICMP_PREC_VIOLATION
		{ ICMP_DEST_UNREACH,  ICMP_PREC_VIOLATION, "Precedence Violation",                        },
		#endif
		#ifdef ICMP_PREC_CUTOFF
		{ ICMP_DEST_UNREACH,  ICMP_PREC_CUTOFF,    "Precedence Cutoff",                           },
		#endif
		{ ICMP_REDIRECT,      ICMP_REDIR_NET,      "Redirect Network",                            },
		{ ICMP_REDIRECT,      ICMP_REDIR_HOST,     "Redirect Host",                               },
		{ ICMP_REDIRECT,      ICMP_REDIR_NETTOS,   "Redirect Type of Service and Network",        },
		{ ICMP_REDIRECT,      ICMP_REDIR_HOSTTOS,  "Redirect Type of Service and Host",           },
		{ ICMP_TIME_EXCEEDED, ICMP_EXC_TTL,        "Time to live exceeded",                       },
		{ ICMP_TIME_EXCEEDED, ICMP_EXC_FRAGTIME,   "Frag reassembly time exceeded",               },
	};

	t_icmp_desc const * p;
	for (p = icmp_desc; p < icmp_desc + FT_ARRAY_SIZE(icmp_desc); p++)
	{
		if (p->type == _icmp->icmp_type && p->code == _icmp->icmp_code)
		{
			break;
		}
	}

	if (p < icmp_desc + FT_ARRAY_SIZE(icmp_desc))
	{
		printf("%s\n", p->desc);
	}
	else
	{
		t_char const * msg;

		switch (_icmp->icmp_type)
		{
			case ICMP_DEST_UNREACH:
				msg = "Dest Unreachable";
				break;
			case ICMP_REDIRECT:
				msg = "Redirect";
				break;
			case ICMP_TIME_EXCEEDED:
				msg = "Time exceeded";
				break;
			default:
				msg = nullptr;
				break;
		}

		printf("%s, Unknown Code: %d\n", msg, _icmp->icmp_code);
	}

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_VERBOSE))
	{
		_print_ip(_ctx, _icmp);
	}
}

static t_void
_print_parameterprob(
	t_ctx const * _ctx,
	struct icmp const * _icmp
)
{
	printf("Parameter problem: IP address = %s\n", _addr_to_str(&_icmp->icmp_gwaddr));
	_print_ip(_ctx, _icmp);
}

static t_void
_print_error(
	t_ctx const * _ctx,
	struct icmp const * _icmp,
	struct sockaddr_in const * _src,
	t_ssize _recv_len
)
{
	typedef struct
	{
		t_uint_8 type;
		t_char const * text;
		t_void (*handler)(t_ctx const *, struct icmp const *);
	} t_icmp_map;

	static t_icmp_map const icmp_map[] =
	{
		{ ICMP_SOURCE_QUENCH,   "Source Quench",        _print_ip,            },
		{ ICMP_DEST_UNREACH,    nullptr,                _print_icmp,          },
		{ ICMP_REDIRECT,        nullptr,                _print_icmp,          },
		{ ICMP_TIME_EXCEEDED,   nullptr,                _print_icmp,          },
		{ ICMP_PARAMETERPROB,   nullptr,                _print_parameterprob, },
		{ ICMP_ECHO,            "Echo Request",         nullptr,              },
		{ ICMP_ECHOREPLY,       "Echo Reply",           nullptr,              },
		{ ICMP_TIMESTAMP,       "Timestamp",            nullptr,              },
		{ ICMP_TIMESTAMPREPLY,  "Timestamp Reply",      nullptr,              },
		{ ICMP_INFO_REQUEST,    "Information Request",  nullptr,              },
		{ ICMP_INFO_REPLY,      "Information Reply",    nullptr,              },
		{ ICMP_ADDRESS,         "Address Mask Request", nullptr,              },
		{ ICMP_ADDRESSREPLY,    "Address Mask Reply",   nullptr,              },
		// { ICMP_ROUTERADV,       "Router Advertisement", nullptr,              },
		// { ICMP_ROUTERDISCOVERY, "Router Discovery",     nullptr,              },
	};

	struct ip const * ip = &_icmp->icmp_ip;

	if (!(FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_VERBOSE) || ip->ip_dst.s_addr == _ctx->dst_addr.sin_addr.s_addr))
	{
		return;
	}

	printf("%lld bytes from %s: ", _recv_len - (ip->ip_hl << 2), _sockaddr_to_str(_src, FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_NUMERIC)));

	t_icmp_map const * p;
	for (p = icmp_map; p < icmp_map + FT_ARRAY_SIZE(icmp_map); p++)
	{
		if (p->type == _icmp->icmp_type)
		{
			break;
		}
	}

	if (p < icmp_map + FT_ARRAY_SIZE(icmp_map))
	{
		if (p->text != nullptr)
		{
			printf("%s\n", p->text);
		}

		if (p->handler != nullptr)
		{
			p->handler(_ctx, _icmp);
		}

		return;
	}

	printf("Bad ICMP type: %d\n", _icmp->icmp_type);
}

// Receive ---------------------------------------------------------------------
static t_void
_print_echo(
	t_ctx * _ctx,
	struct ip const * _ip,
	struct icmp const * _icmp,
	struct sockaddr_in const * _src,
	t_ssize _recv_len,
	t_bool _is_duplicate
)
{
	_recv_len -= (_ip->ip_hl << 2);

	t_double time_ack = 0.0;

	/* Do timing */
	if (IS_TIMEABLE(_recv_len - ICMP_MINLEN))
	{
		struct timeval now;
		gettimeofday(&now, nullptr);

		struct timeval const * then;
		then = (struct timeval const *) _icmp->icmp_data;

		_time_sub(&now, then);

		time_ack = ((t_double) now.tv_sec) * 1000.0 + ((t_double) now.tv_usec) / 1000.0;

		_ctx->stats.time_min = FT_MATH_MIN(_ctx->stats.time_min, time_ack);
		_ctx->stats.time_max = FT_MATH_MAX(_ctx->stats.time_max, time_ack);
		_ctx->stats.time_total += time_ack;
		_ctx->stats.time_total_squared += time_ack * time_ack;
	}

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_QUIET))
	{
		return;
	}

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_FLOOD))
	{
		ft_io_out_chr('\b');
		return;
	}

	printf("%lld bytes from %s: icmp_seq=%u ttl=%d", _recv_len, _sockaddr_to_str(_src, true), ntohs(_icmp->icmp_seq), _ip->ip_ttl);

	if (IS_TIMEABLE(_recv_len - ICMP_MINLEN))
	{
		printf(" time=%.3f ms", time_ack);
	}

	if (_is_duplicate)
	{
		printf(" (DUP!)");
	}

	printf("\n");
}

static t_void
_ping_receive(
	t_ctx * _ctx
)
{
	t_byte ctrl[1024];

	struct sockaddr_in src_addr = { 0 };
	struct iovec iov =
	{
		.iov_base = _ctx->packet,
		.iov_len = sizeof(_ctx->packet)
	};
	struct msghdr msg =
	{
		.msg_control = ctrl,
		.msg_controllen = sizeof(ctrl),
		.msg_flags = 0,
		.msg_iov = &iov,
		.msg_iovlen = 1,
		.msg_name = &src_addr,
		.msg_namelen = sizeof(src_addr)
	};

	t_ssize recv_len = recvmsg(_ctx->socket, &msg, MSG_DONTWAIT);

	if (recv_len < 0)
	{
		return;
	}

	struct ip const * ip = (struct ip const *) _ctx->packet;

	if (recv_len < ((ip->ip_hl << 2) + ICMP_MINLEN))
	{
		dprintf(2, "ft_ping: packet too short (%lld bytes) from %s\n", recv_len, _sockaddr_to_str(&src_addr, true));
		return;
	}

	struct icmp * icmp = (struct icmp *) (_ctx->packet + (ip->ip_hl << 2));

	// Verify checksum
	t_uint_16 const checksum = icmp->icmp_cksum;
	icmp->icmp_cksum = 0;
	icmp->icmp_cksum = ft_mem_checksum_16(icmp, recv_len - (ip->ip_hl << 2));

	switch (icmp->icmp_type)
	{
		case ICMP_ECHOREPLY:
		case ICMP_TIMESTAMPREPLY:
		case ICMP_ADDRESSREPLY:
		{
			if (ntohs(icmp->icmp_id) != _ctx->identifier)
			{
				return;
			}

			if (icmp->icmp_cksum != checksum)
			{
				dprintf(2, "ft_ping: checksum mismatch from %s\n", _sockaddr_to_str(&src_addr, true));
			}

			t_bool is_duplicate = false;

			if (PING_ACK_ISSET(ntohs(icmp->icmp_seq)))
			{
				_ctx->stats.duplicated++;
				is_duplicate = true;
			}
			else
			{
				_ctx->stats.received++;
				PING_ACK_SET(ntohs(icmp->icmp_seq));
			}

			_print_echo(_ctx, ip, icmp, &src_addr, recv_len, is_duplicate);
			break;
		}
		case ICMP_ECHO:
		case ICMP_TIMESTAMP:
		case ICMP_ADDRESS:
		{
			return;
		}
		default:
		{
			struct ip const * orig_ip = &icmp->icmp_ip;
			struct icmp const * orig_icmp = (struct icmp *)(orig_ip + 1);

			// is not my reply ?
			if (!(
				   orig_ip->ip_dst.s_addr == _ctx->dst_addr.sin_addr.s_addr
				&& orig_ip->ip_p == IPPROTO_ICMP
				&& orig_icmp->icmp_type == ICMP_ECHO
				&& ntohs(orig_icmp->icmp_id) == _ctx->identifier
			))
			{
				return;
			}

			_print_error(_ctx, icmp, &src_addr, recv_len);

			_ctx->stats.failed++;
		}
	}
}

// Send ------------------------------------------------------------------------
static t_void
_ping_transmit(
	t_ctx * _ctx
)
{
	struct icmp * icmp = (struct icmp *) _ctx->packet;

	// Header
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = htons(_ctx->stats.transmitted);
	icmp->icmp_id = htons(_ctx->identifier);

	size_t i = 0;

	// Time
	if (IS_TIMEABLE(_ctx->options.size))
	{
		gettimeofday((struct timeval *)icmp->icmp_data, nullptr);

		i += sizeof(struct timeval);
	}

	// Pattern
	for (/**/; i < _ctx->options.size; i++)
	{
		icmp->icmp_data[i] = _ctx->options.pattern.data[i % _ctx->options.pattern.length];
	}

	// Checksum
	t_size packet_len = _ctx->options.size + ICMP_MINLEN;

	icmp->icmp_cksum = ft_mem_checksum_16(_ctx->packet, packet_len);

	// Clear ACK
	PING_ACK_UNSET(_ctx->stats.transmitted);

	// Send
	t_ssize sent_len = sendto(_ctx->socket, _ctx->packet, packet_len, 0, (struct sockaddr *) &_ctx->dst_addr, sizeof(struct sockaddr_in));

	if (sent_len < 0)
	{
		dprintf(2, "sending packet: %s\n", strerror(errno));
		ft_exit(FT_EXIT_ERR);
	}
	else
	{
		_ctx->stats.transmitted++;

		if (sent_len != packet_len)
		{
			printf("ping: wrote %s %lld chars, ret=%lld\n", _ctx->dst_name, packet_len, sent_len);
		}
	}
}

// Run -------------------------------------------------------------------------
static t_void
_print_start(
	t_ctx const * _ctx
)
{
	printf("PING %s (%s): %zu data bytes", _ctx->dst_name, _sockaddr_to_str(&_ctx->dst_addr, true), _ctx->options.size);

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_VERBOSE))
	{
		printf(", id 0x%04x = %u", _ctx->identifier, _ctx->identifier);
	}

	printf("\n");
};

static t_void
_print_end(
	t_ctx const * _ctx
)
{
	printf("--- %s ping statistics ---\n", _ctx->dst_name);
	printf("%llu packets transmitted, ", _ctx->stats.transmitted);
	printf("%llu packets received, ", _ctx->stats.received);

	if (_ctx->stats.duplicated > 0)
	{
		printf("+%llu duplicates, ", _ctx->stats.duplicated);
	}

	// Note: Comment if unwanted
	if (_ctx->stats.failed > 0)
	{
		printf("+%llu fails, ", _ctx->stats.failed);
	}

	if (_ctx->stats.transmitted > 0 && _ctx->stats.received <= _ctx->stats.transmitted)
	{
		printf("%lld%% packet loss",
			(((_ctx->stats.transmitted - _ctx->stats.received) * 100) / _ctx->stats.transmitted)
		);
	}

	// Note: Comment if unwanted
	{
		struct timeval now;
		gettimeofday(&now, nullptr);

		_time_sub(&now, &_ctx->started_at);

		printf(", time %.1f ms", ((t_double) now.tv_sec) * 1000.0 + ((t_double) now.tv_usec) / 1000.0);
	}

	if (_ctx->stats.transmitted > 0 && _ctx->stats.received > _ctx->stats.transmitted)
	{
		printf("-- somebody is printing forged packets!");
	}

	printf("\n");

	if (_ctx->stats.received > 0 && IS_TIMEABLE(_ctx->options.size))
	{
		t_double total = _ctx->stats.received + _ctx->stats.duplicated;
		t_double average = _ctx->stats.time_total / total;
		t_double variance = _ctx->stats.time_total_squared / total - average * average;

		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
			_ctx->stats.time_min,
			average,
			_ctx->stats.time_max,
			ft_math_sqrt(variance, 0.0005)
		);
	}
}

static t_int_32
_ping_run(
	t_ctx * _ctx
)
{
	_print_start(_ctx);

	struct timeval interval;

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_FLOOD))
	{
		interval.tv_sec = 0;
		interval.tv_usec = 10000;
	}
	else
	{
		interval.tv_sec = _ctx->options.interval;
		interval.tv_usec = 0;
	}

	t_size i;
	for (i = 0; i < _ctx->options.preload; i++)
	{
		_ping_transmit(_ctx);
	}

	while (!g_stop && (!_ctx->options.count || _ctx->stats.transmitted < _ctx->options.count))
	{
		// Ping
		_ping_transmit(_ctx);

		struct timeval last;
		gettimeofday(&last, NULL);

		if (!FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_QUIET) && FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_FLOOD))
		{
			ft_io_out_chr('.');
		}

		// Pong
		t_bool is_last = false;

		if (_ctx->options.count > 0 && _ctx->stats.transmitted >= _ctx->options.count)
		{
			is_last = true;

			interval.tv_sec = _ctx->options.linger;
			interval.tv_usec = 0;
		}

		struct timeval next;
		next.tv_sec = last.tv_sec + interval.tv_sec;
		next.tv_usec = last.tv_usec + interval.tv_usec;

		while (next.tv_usec > 1000000)
		{
			next.tv_usec -= 1000000;
			next.tv_sec += 1;
		}

		do
		{
			_ping_receive(_ctx);

			if (is_last && (_ctx->stats.received + _ctx->stats.duplicated + _ctx->stats.failed) >= _ctx->options.count)
			{
				break;
			}

			struct timeval now;
			gettimeofday(&now, nullptr);

			struct timeval diff = next;
			_time_sub(&diff, &now);

			if (diff.tv_sec < 0 || diff.tv_usec < 0)
			{
				break;
			}

		} while (!g_stop);
	}

	_print_end(_ctx);

	return (_ctx->stats.received == 0);
}

// Context ---------------------------------------------------------------------
static t_void
_ctx_stats_clear(
	t_ctx * _ctx
)
{
	_ctx->stats.transmitted = 0;
	_ctx->stats.received = 0;
	_ctx->stats.duplicated = 0;
	_ctx->stats.failed = 0;

	ft_mem_clear(_ctx->stats.ack, ACK_TAB_SIZE);

	_ctx->stats.time_min = 999999999.0;
	_ctx->stats.time_max = 0.0;
	_ctx->stats.time_total = 0.0;
	_ctx->stats.time_total_squared = 0.0;
}

static t_void
_ctx_set_dst(
	t_ctx * _ctx,
	t_char const * _dst
)
{
	struct addrinfo hints =
	{
		.ai_family = AF_INET,
		.ai_protocol = IPPROTO_ICMP,
		.ai_socktype = SOCK_RAW,
		.ai_flags = AI_CANONNAME
	};

	struct addrinfo * infos;

	t_int_32 gai_error = getaddrinfo(_dst, nullptr, &hints, &infos);

	if (gai_error != 0)
	{
		dprintf(2, "ft_ping: %s: %s\n", _dst, gai_strerror(gai_error));
		ft_exit(FT_EXIT_ERR);
	}

	struct addrinfo * info = infos;

	ft_mem_copy(info->ai_addr, &_ctx->dst_addr, info->ai_addrlen);
	ft_str_copy(info->ai_canonname ? info->ai_canonname : _dst, _ctx->dst_name);

	freeaddrinfo(infos);
}

static t_void
_ctx_socket_configure(
	t_ctx * _ctx
)
{
	t_uint_8 enabled = 1;

	setsockopt(_ctx->socket, SOL_SOCKET, SO_BROADCAST, &enabled, sizeof(enabled));

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_DEBUG))
	{
		setsockopt(_ctx->socket, SOL_SOCKET, SO_DEBUG, &enabled, sizeof(enabled));
	}

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_DONTROUTE))
	{
		setsockopt(_ctx->socket, SOL_SOCKET, SO_DONTROUTE, &enabled, sizeof(enabled));
	}

	if (_ctx->options.ttl > 0)
	{
		if (setsockopt(_ctx->socket, SOL_IP, IP_TTL, &_ctx->options.ttl, sizeof(_ctx->options.ttl)) < 0)
		{
			dprintf(2, "ft_ping: setsockopt(IP_TTL): %s\n", strerror(errno));
		}
	}

	if (_ctx->options.tos >= 0)
	{
		if (setsockopt(_ctx->socket, SOL_IP, IP_TOS, &_ctx->options.tos, sizeof(_ctx->options.tos)) < 0)
		{
			dprintf(2, "ft_ping: setsockopt(IP_TOS): %s\n", strerror(errno));
		}
	}
}

static t_void
_ctx_init(
	t_ctx * _ctx
)
{
	_ctx->identifier = getpid() & 0xFFFF; // Note: Mask required to fit in ICMP id
	_ctx->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

	if (_ctx->socket <= 0)
	{
		dprintf(2, "ft_ping: socket: %s\n", strerror(errno));
		ft_exit(FT_EXIT_ERR);
	}

	gettimeofday(&_ctx->started_at, nullptr);

	ft_mem_clear( _ctx->dst_name, sizeof(_ctx->dst_name));
	ft_mem_clear(&_ctx->dst_addr, sizeof(_ctx->dst_addr));
	ft_mem_clear( _ctx->packet,   sizeof(_ctx->packet));

	// Options
	ft_mem_clear(&_ctx->options.flags, sizeof(_ctx->options.flags));
	ft_mem_clear( _ctx->options.hosts, sizeof(_ctx->options.hosts));

	_ctx->options.count = DEFAULT_COUNT;
	_ctx->options.interval = DEFAULT_INTERVAL;
	_ctx->options.linger = DEFAULT_LINGER;
	_ctx->options.preload = DEFAULT_PRELOAD;
	_ctx->options.size = DEFAULT_SIZE;
	_ctx->options.timeout = DEFAULT_TIMEOUT;
	_ctx->options.tos = DEFAULT_TOS;
	_ctx->options.ttl = DEFAULT_TTL;

	ft_mem_copy(DEFAULT_PATTERN, _ctx->options.pattern.data, DEFAULT_PATTERN_SIZE);
	_ctx->options.pattern.length = DEFAULT_PATTERN_SIZE;

	// Stats
	_ctx_stats_clear(_ctx);
}

// Arguments -------------------------------------------------------------------
static t_void
_parse_args(
	t_ctx * _ctx,
	t_int_32 _argc,
	t_char const * _argv[]
)
{
	t_size host_index = 0;

	t_int_32 i;
	for (i = 1; i < _argc; i++)
	{
		t_char const * arg = _argv[i];

		// Destination
		if (arg[0] != '-')
		{
			if (host_index >= HOST_TAB_SIZE)
			{
				dprintf(2, "ft_ping: %s: too many hosts defined (%d max)\n", arg, HOST_TAB_SIZE);
				ft_exit(FT_EXIT_ERR);
			}

			_ctx->options.hosts[host_index++] = arg;

			continue;
		}

		// Flags (short)
		if (arg[1] != '-')
		{
			t_char const * cursor = arg;

			while (*++cursor != '\0')
			{
				switch (*cursor)
				{
					case 'd':
						FT_MEM_BIT_SET(_ctx->options.flags, OPT_DEBUG);
						break;
					case 'f':
						FT_MEM_BIT_SET(_ctx->options.flags, OPT_FLOOD);
						break;
					case 'h':
					case '?':
						printf(USAGE);
						ft_exit(FT_EXIT_OK);
					case 'n':
						FT_MEM_BIT_SET(_ctx->options.flags, OPT_NUMERIC);
						break;
					case 'q':
						FT_MEM_BIT_SET(_ctx->options.flags, OPT_QUIET);
						break;
					case 'r':
						FT_MEM_BIT_SET(_ctx->options.flags, OPT_DONTROUTE);
						break;
					case 'v':
						FT_MEM_BIT_SET(_ctx->options.flags, OPT_VERBOSE);
						break;
					default:
						dprintf(2, "ft_ping: invalid option -- '%c'\n", *cursor);
						ft_exit(FT_EXIT_ERR);
				}
			}

			if (cursor - arg == 1)
			{
				dprintf(2, "ft_ping: invalid option -- ''\n");
				ft_exit(FT_EXIT_ERR);
			}

			continue;
		}

		// Flags (long)
		if (ft_str_find_str(arg, "--pattern=") == arg)
		{
			t_char const * pattern = arg + 10;

			t_char const * cursor;
			for (cursor = pattern; *cursor != '\0'; cursor++)
			{
				if (!ft_chr_is_hex(*cursor))
				{
					dprintf(2, "ft_ping: invalid argument: --pattern='%s': must be in hex format\n", pattern);
					ft_exit(FT_EXIT_ERR);
				}
			}

			if (cursor == pattern)
			{
				dprintf(2, "ft_ping: invalid argument: ''\n");
				ft_exit(FT_EXIT_ERR);
			}

			_ctx->options.pattern.length = 0;

			int j;
			for (j = 0; j < 2 * PATTERN_TAB_SIZE; j += 2)
			{
				if (pattern[j] == '\0')
				{
					break;
				}

				t_char hex[2] = { pattern[j], pattern[j + 1] };

				if (pattern[j + 1] == '\0')
				{
					hex[0] = '0';
					hex[1] = pattern[j];
				}

				_ctx->options.pattern.data[_ctx->options.pattern.length++] = ft_mem_hex_to_byte(hex);

				if (pattern[j + 1] == '\0')
				{
					break;
				}
			}

			FT_MEM_BIT_SET(_ctx->options.flags, OPT_PATTERN);

			continue;
		}

		typedef struct s_opt
		{
			t_char * prefix;
			t_uint_32 flag;
			t_int_32 min;
			t_int_32 max;
			t_int_32 * store;
		} t_opt;

		t_opt const opts[] =
		{
			{ "--count=",    OPT_COUNT,    0, FT_INT_32_MAX, &_ctx->options.count },
			{ "--interval=", OPT_INTERVAL, 1, FT_INT_32_MAX, &_ctx->options.interval },
			{ "--size=",     OPT_SIZE,     0, DATA_SIZE_MAX, &_ctx->options.size },
			{ "--tos=",      OPT_TOS,      0, FT_UINT_8_MAX, &_ctx->options.tos },
			{ "--ttl=",      OPT_TTL,      1, FT_UINT_8_MAX, &_ctx->options.ttl },
			{ "--linger=",   OPT_LINGER,   1, FT_INT_32_MAX, &_ctx->options.linger },
			{ "--preload=",  OPT_PRELOAD,  0, FT_INT_32_MAX, &_ctx->options.preload },
			{ "--timeout=",  OPT_TIMEOUT,  1, FT_INT_32_MAX, &_ctx->options.timeout }
		};

		t_int_32 j;
		for (j = 0; j < FT_ARRAY_SIZE(opts); j++)
		{
			t_opt const * opt = &opts[j];
			t_size const prefix_len = ft_str_length(opt->prefix);

			if (ft_str_find_str(arg, opt->prefix) == arg)
			{
				t_char const * cursor = ft_str_to_int_32(&arg[prefix_len], opt->store);

				if (cursor == 0 || cursor == &arg[prefix_len] || *cursor != '\0')
				{
					dprintf(2, "ft_ping: invalid argument: %s'%s'\n", opt->prefix, &arg[prefix_len]);
					ft_exit(FT_EXIT_ERR);
				}
				if (*opt->store < opt->min || *opt->store > opt->max)
				{
					dprintf(2, "ft_ping: invalid argument: %s'%s': out of range: %ld <= value <= %ld\n", opt->prefix, &arg[prefix_len], opt->min, opt->max);
					ft_exit(FT_EXIT_ERR);
				}

				FT_MEM_BIT_SET(_ctx->options.flags, opt->flag);

				break;
			}
		}

		if (j >= FT_ARRAY_SIZE(opts))
		{
			dprintf(2, "ft_ping: invalid option -- '%s'\n", arg);
			ft_exit(FT_EXIT_ERR);
		}
	}

	if (host_index == 0)
	{
		dprintf(2, "ft_ping: usage error: at least 1 destination is required\n");
		ft_exit(FT_EXIT_ERR);
	}

	_ctx->options.hosts[host_index] = nullptr;

	if (FT_MEM_BIT_ISSET(_ctx->options.flags, OPT_FLOOD & OPT_INTERVAL))
	{
		dprintf(2, "ft_ping: usage error: -f and -i incompatible options\n");
		ft_exit(FT_EXIT_ERR);
	}
}

// Main ------------------------------------------------------------------------
t_int_32
main(
	t_int_32 argc,
	t_char const * argv[]
)
{
	if (getuid() != 0)
	{
		dprintf(2, "ft_ping: sudo priviledge required\n");
		ft_exit(FT_EXIT_ERR);
	}

	t_ctx ctx;

	_ctx_init(&ctx);
	_parse_args(&ctx, argc, argv);
	_ctx_socket_configure(&ctx);

	signal(SIGINT, _signal_handler);

	if (ctx.options.timeout > 0)
	{
		signal(SIGALRM, _signal_handler);
		alarm(ctx.options.timeout);
	}

	t_int_32 status = 0;

	t_size i;
	for (i = 0; ctx.options.hosts[i] != nullptr; i++)
	{
		_ctx_stats_clear(&ctx);
		_ctx_set_dst(&ctx, ctx.options.hosts[i]);
		status |= _ping_run(&ctx);
	}

	close(ctx.socket);

	return status;
}
