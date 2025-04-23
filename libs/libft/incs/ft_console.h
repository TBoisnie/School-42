#ifndef LIBFT_CONSOLE_H
#define LIBFT_CONSOLE_H

#include "ft_preprocessor.h"
#include "ft_types.h"

// Define ----------------------------------------------------------------------
#define FT_CONSOLE_FD_IN  (0)
#define FT_CONSOLE_FD_OUT (1)
#define FT_CONSOLE_FD_ERR (2)

// Todo: Improve
// Note: Console (global?) struct + enums to save enabled flags
#define FT_CONSOLE_STYLE_DEFAULT         "\033[0m"

#define FT_CONSOLE_STYLE_BOLD            "\033[1m"
#define FT_CONSOLE_STYLE_DIM             "\033[2m"
#define FT_CONSOLE_STYLE_UNDERLINE       "\033[4m"
#define FT_CONSOLE_STYLE_HIDEN           "\033[8m"

#define FT_CONSOLE_STYLE_RESET_BOLD      "\033[21m"
#define FT_CONSOLE_STYLE_RESET_DIM       "\033[22m"
#define FT_CONSOLE_STYLE_RESET_UNDERLINE "\033[24m"
#define FT_CONSOLE_STYLE_RESET_HIDEN     "\033[28m"

#define FT_CONSOLE_COLOR_BLACK           "\033[30m"
#define FT_CONSOLE_COLOR_DARK_RED        "\033[31m"
#define FT_CONSOLE_COLOR_DARK_GREEN      "\033[32m"
#define FT_CONSOLE_COLOR_DARK_YELLOW     "\033[33m"
#define FT_CONSOLE_COLOR_DARK_BLUE       "\033[34m"
#define FT_CONSOLE_COLOR_DARK_MAGENTA    "\033[35m"
#define FT_CONSOLE_COLOR_DARK_CYAN       "\033[36m"
#define FT_CONSOLE_COLOR_GRAY            "\033[37m"

#define FT_CONSOLE_COLOR_DARK_GRAY       "\033[90m"
#define FT_CONSOLE_COLOR_RED             "\033[91m"
#define FT_CONSOLE_COLOR_GREEN           "\033[92m"
#define FT_CONSOLE_COLOR_YELLOW          "\033[93m"
#define FT_CONSOLE_COLOR_BLUE            "\033[94m"
#define FT_CONSOLE_COLOR_MAGENTA         "\033[95m"
#define FT_CONSOLE_COLOR_CYAN            "\033[96m"
#define FT_CONSOLE_COLOR_WHITE           "\033[97m"

// Function --------------------------------------------------------------------

#endif
