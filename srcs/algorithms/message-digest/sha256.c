#include <unistd.h>
#include "algorithms/hash.h"

// Define ----------------------------------------------------------------------
#define CHUNK_SIZE  64  // 512 bits

// Macro -----------------------------------------------------------------------
#define CH(x,y,z)   (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x,y,z)  (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

#define SIG_UPPER_0(x)  \
	(FT_MEM_BIT_ROTATE_RIGHT_32(x,2) ^ FT_MEM_BIT_ROTATE_RIGHT_32(x,13) ^ FT_MEM_BIT_ROTATE_RIGHT_32(x,22))
#define SIG_UPPER_1(x)  \
	(FT_MEM_BIT_ROTATE_RIGHT_32(x,6) ^ FT_MEM_BIT_ROTATE_RIGHT_32(x,11) ^ FT_MEM_BIT_ROTATE_RIGHT_32(x,25))

#define SIG_LOWER_0(x)  \
	(FT_MEM_BIT_ROTATE_RIGHT_32(x, 7) ^ FT_MEM_BIT_ROTATE_RIGHT_32(x,18) ^ ((x) >>  3))
#define SIG_LOWER_1(x)  \
	(FT_MEM_BIT_ROTATE_RIGHT_32(x,17) ^ FT_MEM_BIT_ROTATE_RIGHT_32(x,19) ^ ((x) >> 10))

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
		t_byte  state_8 [SHA256_DIGEST_SIZE];
		t_dword state_32[SHA256_DIGEST_SIZE / sizeof(t_dword)];
	};

	t_size size;
};

// Static ----------------------------------------------------------------------
static t_void
_sha256_init(
	t_ctx * _ctx
)
{
	_ctx->chunk_length = 0;

	_ctx->state_32[0] = 0x6a09e667;
	_ctx->state_32[1] = 0xbb67ae85;
	_ctx->state_32[2] = 0x3c6ef372;
	_ctx->state_32[3] = 0xa54ff53a;
	_ctx->state_32[4] = 0x510e527f;
	_ctx->state_32[5] = 0x9b05688c;
	_ctx->state_32[6] = 0x1f83d9ab;
	_ctx->state_32[7] = 0x5be0cd19;

	_ctx->size = 0;
}

static t_void
_sha256_transform(
	t_ctx * _ctx
)
{
	static t_dword const k[64] =
	{
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
		0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
		0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
		0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
		0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
		0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

	t_size i;
	t_dword m[64];

	for ( i = 0 ; i < 16 ; i++ )
	{
		m[i] = ft_sys_to_big_endian_32(_ctx->chunk_32[i]);
	}

	for ( i = 16 ; i < 64 ; i++ )
	{
		m[i] = SIG_LOWER_1(m[i - 2]) + m[i - 7] + SIG_LOWER_0(m[i - 15]) + m[i - 16];
	}

	t_dword a, b, c, d, e, f, g, h;

	a = _ctx->state_32[0];
	b = _ctx->state_32[1];
	c = _ctx->state_32[2];
	d = _ctx->state_32[3];
	e = _ctx->state_32[4];
	f = _ctx->state_32[5];
	g = _ctx->state_32[6];
	h = _ctx->state_32[7];

	t_dword t1, t2;

	for ( i = 0 ; i < 64 ; i++ )
	{
		t1 = h + SIG_UPPER_1(e) + CH(e,f,g) + k[i] + m[i];
		t2 = SIG_UPPER_0(a) + MAJ(a,b,c);
		h = g;
		g = f;
		f = e;
		e = d + t1;
		d = c;
		c = b;
		b = a;
		a = t1 + t2;
	}

	_ctx->state_32[0] += a;
	_ctx->state_32[1] += b;
	_ctx->state_32[2] += c;
	_ctx->state_32[3] += d;
	_ctx->state_32[4] += e;
	_ctx->state_32[5] += f;
	_ctx->state_32[6] += g;
	_ctx->state_32[7] += h;
}

static t_void
_sha256_update(
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
			_sha256_transform(_ctx);
			_ctx->chunk_length = 0;
		}
	}
}

static t_void
_sha256_final(
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
		ft_sys_to_big_endian_64(_ctx->size * 8)
	};

	_sha256_update(_ctx, padding, padding_size);
	_sha256_update(_ctx, (t_byte const *) data_size_in_bits, MESSAGE_LENGTH_SIZE);

	#undef MESSAGE_LENGTH_SIZE

	t_size i;

	for ( i = 0 ; i < FT_ARRAY_SIZE(_ctx->state_32) ; i++ )
	{
		_ctx->state_32[i] = ft_sys_to_big_endian_32(_ctx->state_32[i]);
	}

	ft_mem_copy(_ctx->state_8, _digest, SHA256_DIGEST_SIZE);

	// Clear sensitive information
	ft_mem_clear(_ctx, sizeof(*_ctx));

	#undef THRESHOLD
}

// Function --------------------------------------------------------------------
t_void
sha256_memory(
	t_byte _digest[/* SHA256_DIGEST_SIZE */],
	t_byte const * _mem,
	t_size _size
)
{
	t_ctx ctx;

	_sha256_init(&ctx);
	_sha256_update(&ctx, _mem, _size);
	_sha256_final(&ctx, _digest);
}

t_bool
sha256_file(
	t_byte _digest[/* SHA256_DIGEST_SIZE */],
	t_fd _fd
)
{
	t_ctx ctx;

	_sha256_init(&ctx);

	t_ssize read_length;
	t_byte read_buffer[1024];

	while ( (read_length = read(_fd, read_buffer, sizeof(read_buffer))) > 0 )
	{
		_sha256_update(&ctx, read_buffer, read_length);
	}

	if ( read_length < 0 )
	{
		return (true);
	}

	_sha256_final(&ctx, _digest);

	return (false);
}
