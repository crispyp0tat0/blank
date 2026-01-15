/**
 * @file crc.c
 * @brief CRC-32 checksum calculation implementation.
 * 
 * Implements functions for computing CRC-32 checksums using a lookup table method.
 * 
 * Provides functions to update an existing CRC value with new data and to compute
 * the CRC-32 checksum for a given data block.
 * 
 * Based on the sample implementation from the PNG specification.
 * 
 * @author Gian Carlo Bata
 * @date 2026-01-15
 * @copyright GPL-2.0
 */
#include "crc.h"

#include <stdbool.h>  /* for bool type */
#include <stddef.h>   /* for size_t type */
#include <stdint.h>   /* for uint8_t, uint32_t, uint_fast8_t, and uint_fast16_t types */

/* CRC-32 polynomial */
static const uint32_t POLYNOMIAL = 0xEDB88320u;

/* CRC-32 lookup table flag */
static bool crc_table_initialized = false;

/* CRC-32 lookup table */
static uint32_t crc_table[256];

/* Initialize the CRC-32 lookup table */
static void initialize_crc_table(void)
{
    for (uint_fast16_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (uint_fast8_t j = 0; j < 8; j++) {
            crc = (crc & 1) ? (crc >> 1) ^ POLYNOMIAL : (crc >> 1);
        }
        crc_table[i] = crc;
    }
    crc_table_initialized = true;
}

/* Update the CRC-32 checksum with new data */
uint32_t update_crc(uint32_t crc, const uint8_t *data, const size_t length)
{
    if (!crc_table_initialized) {
        initialize_crc_table();
    }

    for (size_t i = 0; i < length; i++) {
        crc = crc_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
    }

    return crc;
}

/* Compute the CRC-32 checksum for the given data */
uint32_t crc(const uint8_t *data, const size_t length)
{
    return update_crc(0xFFFFFFFF, data, length) ^ 0xFFFFFFFF;
}