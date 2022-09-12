#include "util.h"

void fget_until_char(char *buffer, char delim, size_t n, FILE *stream)
{
    char *curr = &buffer[0];
    while ((*curr = fgetc(stream)) != EOF &&
            *curr != delim && curr - buffer < n) {
        curr++;
    }
    *curr = 0;
}
