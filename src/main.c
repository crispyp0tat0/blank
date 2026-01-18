#include "main.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static int handle_help(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    fprintf(stdout, "This is help\n");
    for (size_t i = 0; i < OPTION_COUNT; i++) {
        fprintf(stdout, "\t%s\t%s\n", options[i].short_code, options[i].description);
    }
    return 0;
}

static int handle_version(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    fprintf(stdout, "%s version %s\n", PROGRAM_NAME, VERSION);
    return 0;
}

option_t options[] = {
    {
        .type = FLAG_HELP,
        .short_code = "-h",
        .long_code = "--help",
        .description = "Show help",
        .requires_value = false,
        .handler = handle_help
    },
    {
        .type = FLAG_VERSION,
        .short_code = "-v",
        .long_code = "--version",
        .description = "Show version",
        .requires_value = false,
        .handler = handle_version
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2) {
        // TODO: Implement something for when there's no command-line argument/s
        fprintf(stderr, "%s: fatal error: No command-line arguments provided.\n", PROGRAM_NAME);
        return 1;
    }

    // test
    for (int i = 1; i < argc; i++) {
        bool matched = false;
        for (size_t j = 0; j < OPTION_COUNT; j++) {
            if (strcmp(argv[i], options[j].short_code) == 0 || strcmp(argv[i], options[j].long_code) == 0) {
                matched = true;
                int ret = options[j].handler(argc, argv);
                return ret;
            }
        }

        if (!matched) {
            fprintf(stderr, "%s: unknown option: %s\n", PROGRAM_NAME, argv[i]);
            return 1;
        }
    }

    return 0;
}