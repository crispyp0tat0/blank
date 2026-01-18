#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>
#include <stddef.h>

// Change these values manually
#define PROGRAM_NAME "blank"
#define VERSION "0.0.0"
#define OPTION_COUNT 2

typedef int (*option_handler)(int argc, char *argv[]);

typedef enum flag_type {
    FLAG_HELP,
    FLAG_VERSION
} flag_type_t;

typedef struct option {
    flag_type_t type;
    const char *short_code;
    const char *long_code;
    const char *description;
    bool requires_value;
    option_handler handler;
} option_t;

extern option_t options[];

#endif // MAIN_H