#ifndef CLEANER_RULES_H
#define CLEANER_RULES_H

#include <stddef.h>

typedef enum {
    RULE_REMOVE_EMPTY_LINES,
    RULE_TRIM_WHITESPACE,
    RULE_REMOVE_DUPLICATE_SPACES,
    RULE_REMOVE_HTML_TAGS,
    RULE_REMOVE_URLS,
    RULE_MAX
} CleanRule;

typedef struct {
    CleanRule rule;
    int enabled;
    const char *description;
} RuleConfig;

void init_default_rules(void);
int apply_rules(char *text, size_t *size);
void set_rule_enabled(CleanRule rule, int enabled);
const char *get_rule_description(CleanRule rule);

#endif 