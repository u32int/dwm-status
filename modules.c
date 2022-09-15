#include "modules.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/statvfs.h>
#include <errno.h>

#include "util.h"

int getloadavg(double loadavg[], int nelem);

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
    static double avg[3];
    if (getloadavg(avg, 3) == -1)
        return "Error: load avg";

    if (arg == NULL || arg[0] == 0) {
        snprintf(glob_buff, 32, "%.2f", avg[0]);
    } else if (!strncmp(arg, "all", 3)){
        snprintf(glob_buff, 32, "%.2f %.2f %.2f", avg[0], avg[1], avg[2]);
    } else {
        return "Error: loadavg invalid argument";
    }

    return glob_buff;
}

const char *mem_used(const char *arg)
{
    FILE *f = fopen("/proc/meminfo", "r");

    static const char *keys[] = {"MemTotal",
                                 "MemFree", "Buffers", "Cached", "SReclaimable"};
    int sum;

    for (size_t i = 0; i < sizeof(keys)/sizeof(keys[0]); ++i) {
        fget_until_char(glob_buff, ':', 32, f);

        if (!strncmp(keys[i], glob_buff, 32)) {
            while (fgetc(f) == ' '); /* advance to number */
            fseek(f, -1, SEEK_CUR);
            fget_until_char(glob_buff, ' ', 32, f);
            if (i == 0) {
                sum = strtol(glob_buff, NULL, 10);
            } else {
                sum -= strtol(glob_buff, NULL, 10);
            }
        } else {
            i--;
        }
        while (fgetc(f) != '\n'); /* advance to next line */
        
    }

    fclose(f);

    if (arg == NULL || arg[1] != '\0') {
        return "[Error: mem_used - arg is NULL or too long]";
    } else {
        switch (arg[0]) {
        case 'K':
            break;
        case 'M':
            sum /= 1024;
            break;
        case 'G':
            sum /= (1024*1024);
            break;
        default:
            return "[Error: mem_used - invalid argument]";
        }
    }

    snprintf(glob_buff, 128, "%d%s", sum, arg);
    return glob_buff;
}


const char *disk_free(const char *path)
{
    struct statvfs fs_stats;

    if (statvfs(path, &fs_stats) == -1) {
        return strerror(errno);
    }

    static const char suffixes[] = {'K', 'M', 'G', 'T'};

    size_t free_kb = fs_stats.f_bsize*fs_stats.f_bavail;
    size_t i = 0;
    while (free_kb > 1024 && i < sizeof(suffixes)) {
        free_kb /= 1024;
        i++;
    }

    snprintf(glob_buff, 128, "%lu%c", free_kb, suffixes[i-1]);
    return glob_buff;
}
