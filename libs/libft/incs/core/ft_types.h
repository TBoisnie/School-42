#ifndef LIBFT_CORE_TYPES_H
#define LIBFT_CORE_TYPES_H

// Define ----------------------------------------------------------------------
#define true     TRUE
#define false    FALSE
#define nullptr  ((void *) 0)

// Typedef ---------------------------------------------------------------------
typedef signed char        t_int_8;
typedef signed short       t_int_16;
typedef signed int         t_int_32;
typedef signed long long   t_int_64;

typedef unsigned char      t_uint_8;
typedef unsigned short     t_uint_16;
typedef unsigned int       t_uint_32;
typedef unsigned long long t_uint_64;

typedef        char        t_char;
typedef signed short       t_short;
typedef signed int         t_int;
typedef signed long        t_long;
typedef signed long long   t_llong;

typedef unsigned char      t_uchar;
typedef unsigned short     t_ushort;
typedef unsigned int       t_uint;
typedef unsigned long      t_ulong;
typedef unsigned long long t_ullong;

typedef float              t_float;
typedef double             t_double;
typedef long double        t_ldouble;

typedef unsigned char      t_byte;
typedef unsigned short     t_word;
typedef unsigned int       t_dword;
typedef unsigned long long t_qword;

typedef unsigned long      t_wchar;

typedef unsigned long long t_size;
typedef signed long long   t_ssize;

typedef unsigned long long t_ptr;
typedef signed long long   t_ptrdiff;

typedef signed int         t_fd;
typedef signed int         t_pid;

typedef void               t_void;

typedef enum e_bool        t_bool;

// Enum ------------------------------------------------------------------------
enum e_bool
{
	FALSE = 0,
	TRUE  = 1,
};

#endif
