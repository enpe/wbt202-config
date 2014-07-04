/** @file */

#ifndef PASSWORD_H
#define PASSWORD_H

#include <stdint.h>

/**
 * @name Password utilities.
 *
 * @{
 */

/**
 * @brief Encode a password.
 */
uint32_t encodePassword( uint32_t p );

/**
 * @brief Decode a password
 */
uint32_t decodePassword( uint32_t p );

/**
 * @brief Check if a password has been set.
 */
bool enabledPassword( uint32_t p );
/** @} */

#endif // PASSWORD_H
