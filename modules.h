#include <stddef.h>

struct module {
    const char *(*func)(const char *);
    const char *arg;
    int delay;
};

const char *text(const char *);
const char *color_fg(const char *);
const char *color_bg(const char *);
const char *color_reset(const char *);

const char *datetime(const char *);
const char *kernel_ver(const char *);
const char *load_avg(const char *);
const char *mem_used(const char *);
const char *disk_free(const char *);
