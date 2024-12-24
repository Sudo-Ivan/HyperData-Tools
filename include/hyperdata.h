#ifndef HYPERDATA_H
#define HYPERDATA_H

#include <stddef.h>

// Return codes
#define HD_SUCCESS 0
#define HD_ERROR   1

// Common utility functions
int file_exists(const char *path);
char *read_file(const char *path, size_t *size);
int write_file(const char *path, const char *data, size_t size);
char *join_path(const char *dir, const char *file);
void free_if_not_null(void *ptr);

// Tool handlers
int handle_clean(int argc, char *argv[]);
int handle_organize(int argc, char *argv[]);
int handle_sort(int argc, char *argv[]);
int handle_format(int argc, char *argv[]);
int handle_convert(int argc, char *argv[]);

#endif