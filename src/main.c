#include <stdio.h>
#include <string.h>
#include "../include/hyperdata.h"

#define VERSION "0.1.0"

void print_usage(void) {
    printf("HyperData-Tools v%s\n", VERSION);
    printf("Usage: hyperdata <command> [options]\n\n");
    printf("Commands:\n");
    printf("  clean     Clean and preprocess data\n");
    printf("  organize  Organize files and data\n");
    printf("  sort      Sort data using various algorithms\n");
    printf("  format    Format data into specific layouts\n");
    printf("  convert   Convert between different formats\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "clean") == 0) {
        return handle_clean(argc - 1, argv + 1);
    } else if (strcmp(command, "organize") == 0) {
        return handle_organize(argc - 1, argv + 1);
    } else if (strcmp(command, "sort") == 0) {
        return handle_sort(argc - 1, argv + 1);
    } else if (strcmp(command, "format") == 0) {
        return handle_format(argc - 1, argv + 1);
    } else if (strcmp(command, "convert") == 0) {
        return handle_convert(argc - 1, argv + 1);
    }

    print_usage();
    return 1;
} 