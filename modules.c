#include "modules.h"

#include <stdio.h>
#include <stdlib.h>
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

const char *load_avg(const char *arg)
{
    double avg[3];
    if (getloadavg(avg, 3) == -1)
        return "Error: load avg";

    snprintf(glob_buff, 32, "%.2f %.2f %.2f", avg[0], avg[1], avg[2]);

    return glob_buff;
}
