#include <unistd.h>
#include "algorithms/hash.h"

// Define ----------------------------------------------------------------------
#define CHUNK_SIZE  64  // 512 bits

// Macro -----------------------------------------------------------------------
#define F(x,y,z)  (((x) & (y)) | (~(x) &  (z)))
#define G(x,y,z)  (((x) & (z)) | ( (y) & ~(z)))
#define H(x,y,z)  ((x) ^ (y) ^ (z))
#define I(x,y,z)  ((y) ^ ((x) | ~(z)))

#define FF(a,b,c,d,m,s,t)  \
	{ \
		a += F(b,c,d) + m + t; \
		a = b + FT_MEM_BIT_ROTATE_LEFT_32(a,s); \
	}
#define GG(a,b,c,d,m,s,t)  \
	{ \
		a += G(b,c,d) + m + t; \
		a = b + FT_MEM_BIT_ROTATE_LEFT_32(a,s); \
	}
#define HH(a,b,c,d,m,s,t)  \
	{ \
		a += H(b,c,d) + m + t; \
		a = b + FT_MEM_BIT_ROTATE_LEFT_32(a,s); \
	}
#define II(a,b,c,d,m,s,t)  \
	{ \
		a += I(b,c,d) + m + t; \
		a = b + FT_MEM_BIT_ROTATE_LEFT_32(a,s); \
	}

// Typedef ---------------------------------------------------------------------
typedef struct s_ctx t_ctx;

// Struct ----------------------------------------------------------------------
struct s_ctx
{
	union
	{
		t_byte  chunk_8 [CHUNK_SIZE];
		t_dword chunk_32[CHUNK_SIZE / sizeof(t_dword)];
	};

	t_size chunk_length;

	union
	{
		t_byte  state_8 [MD5_DIGEST_SIZE];
		t_dword state_32[MD5_DIGEST_SIZE / sizeof(t_dword)];
	};

	t_size size;
};

// Static ----------------------------------------------------------------------
static t_void
_md5_init(
	t_ctx * _ctx
)
{
	_ctx->chunk_length = 0;

	_ctx->state_32[0] = 0x67452301;
	_ctx->state_32[1] = 0xefcdab89;
	_ctx->state_32[2] = 0x98badcfe;
	_ctx->state_32[3] = 0x10325476;

	_ctx->size = 0;
}

static t_void
_md5_transform(
	t_ctx * _ctx
)
{
	t_size i;
	t_dword m[16];

	for ( i = 0 ; i < 16 ; i++ )
	{
		m[i] = ft_sys_to_little_endian_32(_ctx->chunk_32[i]);
	}

	t_dword a, b, c, d;

	a = _ctx->state_32[0];
	b = _ctx->state_32[1];
	c = _ctx->state_32[2];
	d = _ctx->state_32[3];

	FF(a,b,c,d, m[0],   7, 0xd76aa478);
	FF(d,a,b,c, m[1],  12, 0xe8c7b756);
	FF(c,d,a,b, m[2],  17, 0x242070db);
	FF(b,c,d,a, m[3],  22, 0xc1bdceee);
	FF(a,b,c,d, m[4],   7, 0xf57c0faf);
	FF(d,a,b,c, m[5],  12, 0x4787c62a);
	FF(c,d,a,b, m[6],  17, 0xa8304613);
	FF(b,c,d,a, m[7],  22, 0xfd469501);
	FF(a,b,c,d, m[8],   7, 0x698098d8);
	FF(d,a,b,c, m[9],  12, 0x8b44f7af);
	FF(c,d,a,b, m[10], 17, 0xffff5bb1);
	FF(b,c,d,a, m[11], 22, 0x895cd7be);
	FF(a,b,c,d, m[12],  7, 0x6b901122);
	FF(d,a,b,c, m[13], 12, 0xfd987193);
	FF(c,d,a,b, m[14], 17, 0xa679438e);
	FF(b,c,d,a, m[15], 22, 0x49b40821);

	GG(a,b,c,d, m[1],   5, 0xf61e2562);
	GG(d,a,b,c, m[6],   9, 0xc040b340);
	GG(c,d,a,b, m[11], 14, 0x265e5a51);
	GG(b,c,d,a, m[0],  20, 0xe9b6c7aa);
	GG(a,b,c,d, m[5],   5, 0xd62f105d);
	GG(d,a,b,c, m[10],  9, 0x02441453);
	GG(c,d,a,b, m[15], 14, 0xd8a1e681);
	GG(b,c,d,a, m[4],  20, 0xe7d3fbc8);
	GG(a,b,c,d, m[9],   5, 0x21e1cde6);
	GG(d,a,b,c, m[14],  9, 0xc33707d6);
	GG(c,d,a,b, m[3],  14, 0xf4d50d87);
	GG(b,c,d,a, m[8],  20, 0x455a14ed);
	GG(a,b,c,d, m[13],  5, 0xa9e3e905);
	GG(d,a,b,c, m[2],   9, 0xfcefa3f8);
	GG(c,d,a,b, m[7],  14, 0x676f02d9);
	GG(b,c,d,a, m[12], 20, 0x8d2a4c8a);

	HH(a,b,c,d, m[5],   4, 0xfffa3942);
	HH(d,a,b,c, m[8],  11, 0x8771f681);
	HH(c,d,a,b, m[11], 16, 0x6d9d6122);
	HH(b,c,d,a, m[14], 23, 0xfde5380c);
	HH(a,b,c,d, m[1],   4, 0xa4beea44);
	HH(d,a,b,c, m[4],  11, 0x4bdecfa9);
	HH(c,d,a,b, m[7],  16, 0xf6bb4b60);
	HH(b,c,d,a, m[10], 23, 0xbebfbc70);
	HH(a,b,c,d, m[13],  4, 0x289b7ec6);
	HH(d,a,b,c, m[0],  11, 0xeaa127fa);
	HH(c,d,a,b, m[3],  16, 0xd4ef3085);
	HH(b,c,d,a, m[6],  23, 0x04881d05);
	HH(a,b,c,d, m[9],   4, 0xd9d4d039);
	HH(d,a,b,c, m[12], 11, 0xe6db99e5);
	HH(c,d,a,b, m[15], 16, 0x1fa27cf8);
	HH(b,c,d,a, m[2],  23, 0xc4ac5665);

	II(a,b,c,d, m[0],   6, 0xf4292244);
	II(d,a,b,c, m[7],  10, 0x432aff97);
	II(c,d,a,b, m[14], 15, 0xab9423a7);
	II(b,c,d,a, m[5],  21, 0xfc93a039);
	II(a,b,c,d, m[12],  6, 0x655b59c3);
	II(d,a,b,c, m[3],  10, 0x8f0ccc92);
	II(c,d,a,b, m[10], 15, 0xffeff47d);
	II(b,c,d,a, m[1],  21, 0x85845dd1);
	II(a,b,c,d, m[8],   6, 0x6fa87e4f);
	II(d,a,b,c, m[15], 10, 0xfe2ce6e0);
	II(c,d,a,b, m[6],  15, 0xa3014314);
	II(b,c,d,a, m[13], 21, 0x4e0811a1);
	II(a,b,c,d, m[4],   6, 0xf7537e82);
	II(d,a,b,c, m[11], 10, 0xbd3af235);
	II(c,d,a,b, m[2],  15, 0x2ad7d2bb);
	II(b,c,d,a, m[9],  21, 0xeb86d391);

	_ctx->state_32[0] += a;
	_ctx->state_32[1] += b;
	_ctx->state_32[2] += c;
	_ctx->state_32[3] += d;
}

static t_void
_md5_update(
	t_ctx * _ctx,
	t_byte const _data[],
	t_size _data_length
)
{
	while ( _data_length > 0 )
	{
		t_size const n = FT_MATH_MIN(_data_length, CHUNK_SIZE - _ctx->chunk_length);

		ft_mem_copy(_data, &_ctx->chunk_8[_ctx->chunk_length], n);

		_data += n;
		_data_length -= n;
		_ctx->chunk_length += n;
		_ctx->size += n;

		if ( _ctx->chunk_length == CHUNK_SIZE )
		{
			_md5_transform(_ctx);
			_ctx->chunk_length = 0;
		}
	}
}

static t_void
_md5_final(
	t_ctx * _ctx,
	t_byte _digest[]
)
{
	static t_byte const padding[CHUNK_SIZE] =
	{
		0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	#define MESSAGE_LENGTH_SIZE  8

	t_size const padding_size = ( _ctx->chunk_length < (CHUNK_SIZE - MESSAGE_LENGTH_SIZE) )
		? CHUNK_SIZE - MESSAGE_LENGTH_SIZE - _ctx->chunk_length
		: 2 * CHUNK_SIZE - MESSAGE_LENGTH_SIZE - _ctx->chunk_length
	;

	t_qword const data_size_in_bits[MESSAGE_LENGTH_SIZE / sizeof(t_qword)] =
	{
		ft_sys_to_little_endian_64(_ctx->size * 8)
	};

	_md5_update(_ctx, padding, padding_size);
	_md5_update(_ctx, (t_byte const *) data_size_in_bits, MESSAGE_LENGTH_SIZE);

	#undef MESSAGE_LENGTH_SIZE

	t_size i;

	for ( i = 0 ; i < FT_ARRAY_SIZE(_ctx->state_32) ; i++ )
	{
		_ctx->state_32[i] = ft_sys_to_little_endian_32(_ctx->state_32[i]);
	}

	ft_mem_copy(_ctx->state_8, _digest, MD5_DIGEST_SIZE);

	// Clear sensitive information
	ft_mem_clear(_ctx, sizeof(*_ctx));
}

// Function --------------------------------------------------------------------
t_void
md5_memory(
	t_byte _digest[/* MD5_DIGEST_SIZE */],
	t_byte const * _mem,
	t_size _size
)
{
	t_ctx ctx;

	_md5_init(&ctx);
	_md5_update(&ctx, _mem, _size);
	_md5_final(&ctx, _digest);
}

t_bool
md5_file(
	t_byte _digest[/* MD5_DIGEST_SIZE */],
	t_fd _fd
)
{
	t_ctx ctx;

	_md5_init(&ctx);

	t_byte buffer[1024];
	t_ssize length;

	while ( (length = read(_fd, buffer, sizeof(buffer))) > 0 )
	{
		_md5_update(&ctx, buffer, length);
	}

	if ( length < 0 )
	{
		return (true);
	}

	_md5_final(&ctx, _digest);

	return (false);
}
