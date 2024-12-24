#include "rules.h"
#include "../../include/hyperdata.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static RuleConfig rules[RULE_MAX] = {
    {RULE_REMOVE_EMPTY_LINES, 1, "Remove empty or whitespace-only lines"},
    {RULE_TRIM_WHITESPACE, 1, "Trim leading/trailing whitespace"},
    {RULE_REMOVE_DUPLICATE_SPACES, 1, "Replace multiple spaces with single space"},
    {RULE_REMOVE_HTML_TAGS, 0, "Remove HTML/XML tags"},
    {RULE_REMOVE_URLS, 0, "Remove URLs"}
};

void init_default_rules(void) {
    // Default rules already set in static initialization
}

static char *remove_empty_lines(char *text, size_t *size) {
    char *src = text;
    char *dst = text;
    char *line_start = text;
    int empty_line = 1;

    while (*src) {
        if (*src == '\n') {
            if (!empty_line) {
                while (line_start <= src) {
                    *dst++ = *line_start++;
                }
            }
            line_start = src + 1;
            empty_line = 1;
        } else if (!isspace(*src)) {
            empty_line = 0;
        }
        src++;
    }

    if (!empty_line) {
        while (line_start < src) {
            *dst++ = *line_start++;
        }
    }

    *dst = '\0';
    *size = dst - text;
    return text;
}

static char *trim_whitespace(char *text, size_t *size) {
    char *start = text;
    char *end = text + *size - 1;
    char *dst = text;

    while (*start && isspace(*start)) start++;
    while (end > start && isspace(*end)) end--;

    *size = end - start + 1;
    memmove(text, start, *size);
    text[*size] = '\0';
    return text;
}

static char *remove_duplicate_spaces(char *text, size_t *size) {
    char *src = text;
    char *dst = text;
    int prev_space = 0;

    while (*src) {
        if (isspace(*src)) {
            if (!prev_space) {
                *dst++ = ' ';
                prev_space = 1;
            }
        } else {
            *dst++ = *src;
            prev_space = 0;
        }
        src++;
    }

    *dst = '\0';
    *size = dst - text;
    return text;
}

int apply_rules(char *text, size_t *size) {
    if (!text || !size) return HD_ERROR;

    if (rules[RULE_REMOVE_EMPTY_LINES].enabled) {
        text = remove_empty_lines(text, size);
    }
    
    if (rules[RULE_TRIM_WHITESPACE].enabled) {
        text = trim_whitespace(text, size);
    }
    
    if (rules[RULE_REMOVE_DUPLICATE_SPACES].enabled) {
        text = remove_duplicate_spaces(text, size);
    }

    return HD_SUCCESS;
}

void set_rule_enabled(CleanRule rule, int enabled) {
    if (rule < RULE_MAX) {
        rules[rule].enabled = enabled;
    }
}

const char *get_rule_description(CleanRule rule) {
    if (rule < RULE_MAX) {
        return rules[rule].description;
    }
    return NULL;
} 