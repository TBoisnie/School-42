#ifndef FT_SSL_ALGORITHMS_HASH_H
#define FT_SSL_ALGORITHMS_HASH_H

#include "libft/incs/libft.h"

// Define ----------------------------------------------------------------------
#define MD5_DIGEST_SIZE  16
#define SHA256_DIGEST_SIZE  32
#define WHIRLPOOL_DIGEST_SIZE  64

// Function --------------------------------------------------------------------
/**
 * Hash a memory block and store its MD5 digest into the provided buffer.
 *
 * @param _digest: Buffer to store the digest in
 * @param _mem: Memory block to hash
 * @param _size: Size of the memory block
 */
t_void md5_memory(t_byte _digest[MD5_DIGEST_SIZE], t_byte const * _mem, t_size _size);

/**
 * Hash a file and store its MD5 digest into the provided buffer.
 *
 * @param _digest: Buffer to store the digest in
 * @param _fd: File descriptor to read from
 *
 * @return false on success, true otherwise
 */
t_bool md5_file(t_byte _digest[MD5_DIGEST_SIZE], t_fd _fd);

/**
 * Hash a memory block and store its SHA256 digest into the provided buffer.
 *
 * @param _digest: Buffer to store the digest in
 * @param _mem: Memory block to hash
 * @param _size: Size of the memory block
 */
t_void sha256_memory(t_byte _digest[SHA256_DIGEST_SIZE], t_byte const * _mem, t_size _size);

/**
 * Hash a file and store its SHA256 digest into the provided buffer.
 *
 * @param _digest: Buffer to store the digest in
 * @param _fd: File descriptor to read from
 *
 * @return false on success, true otherwise
 */
t_bool sha256_file(t_byte _digest[SHA256_DIGEST_SIZE], t_fd _fd);

/**
 * Hash a memory block and store its Whirlpool digest into the provided buffer.
 *
 * @param _digest: Buffer to store the digest in
 * @param _mem: Memory block to hash
 * @param _size: Size of the memory block
 */
t_void whirlpool_memory(t_byte _digest[WHIRLPOOL_DIGEST_SIZE], t_byte const * _mem, t_size _size);

/**
 * Hash a file and store its Whirlpool digest into the provided buffer.
 *
 * @param _digest: Buffer to store the digest in
 * @param _fd: File descriptor to read from
 *
 * @return false on success, true otherwise
 */
t_bool whirlpool_file(t_byte _digest[WHIRLPOOL_DIGEST_SIZE], t_fd _fd);

#endif
