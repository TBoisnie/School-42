#ifndef LIBFT_SYSTEM_H
#define LIBFT_SYSTEM_H

#include "../core/ft_types.h"

// Define ----------------------------------------------------------------------
#define FT_EXIT_OK   (0)
#define FT_EXIT_ERR  (1)

// Macro -----------------------------------------------------------------------
#define FT_DEVICE_MAJOR(dev)  (((dev) & 0xfff00) >> 8)
#define FT_DEVICE_MINOR(dev)  (((dev) & 0xff) | (((dev) >> 12) & 0xfff00))

// Function --------------------------------------------------------------------
/**
 * Force exit the program.
 *
 * @param _code: exit code
**/
t_void ft_exit(t_int _code);

/**
 * Check if system uses big endianness.
 *
 * @return `true` if system uses big-endian, `false` otherwise
**/
t_bool ft_sys_is_big_endian();

/**
 * Check if system uses big endianness.
 *
 * @return `true` if system uses big-endian, `false` otherwise
**/
t_bool ft_sys_is_little_endian();

/**
 * Convert a 16-bit memory block from system endianness to big-endianness.
 *
 * @return Converted memory block
**/
t_word ft_sys_to_big_endian_16(t_word _mem);

/**
 * Convert a 32-bit memory block from system endianness to big-endianness.
 *
 * @return Converted memory block
**/
t_dword ft_sys_to_big_endian_32(t_dword _mem);

/**
 * Convert a 64-bit memory block from system endianness to big-endianness.
 *
 * @return Converted memory block
**/
t_qword ft_sys_to_big_endian_64(t_qword _mem);

/**
 * Convert a 16-bit memory block from system endianness to little-endianness.
 *
 * @return Converted memory block
**/
t_word ft_sys_to_little_endian_16(t_word _mem);

/**
 * Convert a 32-bit memory block from system endianness to little-endianness.
 *
 * @return Converted memory block
**/
t_dword ft_sys_to_little_endian_32(t_dword _mem);

/**
 * Convert a 64-bit memory block from system endianness to little-endianness.
 *
 * @return Converted memory block
**/
t_qword ft_sys_to_little_endian_64(t_qword _mem);

#endif
