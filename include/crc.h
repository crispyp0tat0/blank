/**
 * @file crc.h
 * @brief CRC-32 checksum calculation interface.
 * 
 * Provides function declarations for computing CRC-32 checksums.
 * 
 * @author Gian Carlo Bata
 * @date 2026-01-15
 * @copyright GPL-2.0
 */
#ifndef CRC_H
#define CRC_H

#include <stddef.h>  /* for size_t type */
#include <stdint.h>  /* for uint8_t and uint32_t types */

/* Update the CRC-32 checksum with new data */
uint32_t update_crc(uint32_t crc, const uint8_t *data, const size_t length);

/* Compute the CRC-32 checksum for the given data */
uint32_t crc(const uint8_t *data, const size_t length);

#endif // CRC_H