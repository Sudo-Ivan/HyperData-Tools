#include "../../include/hyperdata.h"
#include "rules.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void print_cleaner_usage(void) {
    printf("Usage: hyperdata clean [options] <file>\n\n");
    printf("Options:\n");
    printf("  --no-empty-lines    Disable empty line removal\n");
    printf("  --no-trim          Disable whitespace trimming\n");
    printf("  --no-spaces        Disable duplicate space removal\n");
    printf("  --html             Enable HTML tag removal\n");
    printf("  --urls             Enable URL removal\n");
}

int handle_clean(int argc, char *argv[]) {
    if (argc < 2) {
        print_cleaner_usage();
        return HD_ERROR;
    }

    init_default_rules();

    const char *input_file = argv[argc - 1];
    
    // Parse options
    for (int i = 1; i < argc - 1; i++) {
        if (strcmp(argv[i], "--no-empty-lines") == 0) {
            set_rule_enabled(RULE_REMOVE_EMPTY_LINES, 0);
        } else if (strcmp(argv[i], "--no-trim") == 0) {
            set_rule_enabled(RULE_TRIM_WHITESPACE, 0);
        } else if (strcmp(argv[i], "--no-spaces") == 0) {
            set_rule_enabled(RULE_REMOVE_DUPLICATE_SPACES, 0);
        } else if (strcmp(argv[i], "--html") == 0) {
            set_rule_enabled(RULE_REMOVE_HTML_TAGS, 1);
        } else if (strcmp(argv[i], "--urls") == 0) {
            set_rule_enabled(RULE_REMOVE_URLS, 1);
        }
    }

    size_t size;
    char *content = read_file(input_file, &size);
    if (!content) {
        printf("Error: Could not read file %s\n", input_file);
        return HD_ERROR;
    }

    if (apply_rules(content, &size) != HD_SUCCESS) {
        printf("Error: Failed to apply cleaning rules\n");
        free(content);
        return HD_ERROR;
    }

    // Create output filename
    char *output_file = malloc(strlen(input_file) + 7);
    sprintf(output_file, "%s.clean", input_file);

    if (write_file(output_file, content, size) != HD_SUCCESS) {
        printf("Error: Could not write to file %s\n", output_file);
        free(content);
        free(output_file);
        return HD_ERROR;
    }

    printf("Cleaned file saved as: %s\n", output_file);

    free(content);
    free(output_file);
    return HD_SUCCESS;
} 