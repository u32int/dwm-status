#include "modules.h"

#include <stdio.h>
#include <time.h>

static char glob_buff[128];

const char *text(const char *arg)
{
    return arg;
}

const char *color_fg(const char *color)
{
    snprintf(glob_buff, 32, "^c%s^", color);
    return glob_buff;
}

const char *color_bg(const char *color)
{
    snprintf(glob_buff, 32, "^b%s^", color);
    return glob_buff;
}

const char *color_reset(const char *arg)
{
    (void)arg;
    return "^d^";
}

const char *datetime(const char *format)
{
    time_t t = time(NULL);
    if (!strftime(glob_buff, sizeof(glob_buff), format, localtime(&t)))
        return "Error: datetime too long or empty";

    return glob_buff;
}
