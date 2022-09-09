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
