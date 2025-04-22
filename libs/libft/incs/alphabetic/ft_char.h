#ifndef LIBFT_ALPHABETIC_CHAR_H
#define LIBFT_ALPHABETIC_CHAR_H

#include "../core/ft_types.h"

// Function --------------------------------------------------------------------
/**
 * Check if the character _chr is alpha-numeric [a-zA-Z0-9] or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_alnum(t_char _chr);

/**
 * Check if the character _chr is alphabetic [a-zA-Z] or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_alpha(t_char _chr);

/**
 * Check if the character _chr is ascii or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_ascii(t_char _chr);

/**
 * Check if the character _chr is blank (` `, `\\t`) or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_blank(t_char _chr);

/**
 * Check if the character _chr is a digit [0-9] or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_digit(t_char _chr);

/**
 * Check if the character _chr is an hexadecimal [a-fA-F0-9] or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_hex(t_char _chr);

/**
 * Check if the character _chr is printable or not.
 *
 * @param _chr: character to check
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_print(t_char _chr);

/**
 * Check if the character _chr is a space or not.
 *
 * @param _chr: character to convert
 *
 * @return true if it is, false othewise
**/
t_bool ft_chr_is_space(t_char _chr);

/**
 * Convert the character to lower case.
 *
 * @param _chr: character to convert
 *
 * @return converted character
**/
t_char ft_chr_to_lower(t_char _chr);

/**
 * Convert the character to lower case.
 *
 * @param _chr: character to convert
 *
 * @return converted character
**/
t_char ft_chr_to_upper(t_char _chr);

#endif
