#include "crc.h"

#include <stdio.h>

typedef struct crc_test_vector {
    const char *data;
    size_t length;
    uint32_t expected_crc;
} crc_test_vector_t;

static const crc_test_vector_t test_vectors[] = {
    {"", 0, 0x00000000},
    {"123456789", 9, 0xCBF43926},
    {"The quick brown fox jumps over the lazy dog", 43, 0x414FA339},
    {"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", 445, 0x98B2C5BD},
};

int test_update_crc(crc_test_vector_t vector)
{
    uint32_t crc32 = 0xFFFFFFFF; // Initial CRC value

    for (size_t i = 0; i < vector.length; i++) {
        crc32 = update_crc(crc32, (const uint8_t *)&vector.data[i], 1);
    }

    crc32 ^= 0xFFFFFFFF; // Final XOR value

    if (crc32 != vector.expected_crc) {
        return 1;
    }

    return 0;
}


int test_crc(crc_test_vector_t vector)
{
    uint32_t crc32 = crc((const uint8_t *)vector.data, vector.length);
    
    if (crc32 != vector.expected_crc) {
        return 1;
    }
    
    return 0;
}

int main(void)
{
    size_t num_tests = sizeof(test_vectors) / sizeof(test_vectors[0]);
    size_t passed = 0;
    for (size_t i = 0; i < num_tests; i++) {
        if (!test_crc(test_vectors[i]) && !test_update_crc(test_vectors[i])) {
            passed++;
            printf("[PASS] Test %zu/%zu\n", i + 1, num_tests);
        } else {
            printf("[FAIL] Test %zu/%zu\n", i + 1, num_tests);
        }
    }

    printf("Passed %zu out of %zu tests\n", passed, num_tests);

    return 0;
}

