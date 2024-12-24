#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../../include/hyperdata.h"

int file_exists(const char *path) {
    struct stat buffer;
    return stat(path, &buffer) == 0;
}

char *read_file(const char *path, size_t *size) {
    FILE *file = fopen(path, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    *size = ftell(file);
    rewind(file);

    char *buffer = malloc(*size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, *size, file) != *size) {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[*size] = '\0';
    fclose(file);
    return buffer;
}

int write_file(const char *path, const char *data, size_t size) {
    FILE *file = fopen(path, "wb");
    if (!file) return HD_ERROR;

    size_t written = fwrite(data, 1, size, file);
    fclose(file);

    return written == size ? HD_SUCCESS : HD_ERROR;
}

char *join_path(const char *dir, const char *file) {
    size_t dir_len = strlen(dir);
    size_t file_len = strlen(file);
    char *path = malloc(dir_len + file_len + 2);
    
    if (!path) return NULL;

    strcpy(path, dir);
    if (dir[dir_len - 1] != '/') {
        path[dir_len] = '/';
        strcpy(path + dir_len + 1, file);
    } else {
        strcpy(path + dir_len, file);
    }

    return path;
}

void free_if_not_null(void *ptr) {
    if (ptr) free(ptr);
} 