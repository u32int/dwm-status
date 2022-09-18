#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#include <time.h>
int nanosleep(const struct timespec *req, struct timespec *rem);

#include "config.h"

static char status[STATUS_MAX_LEN];
static char cache[MODULES_LEN][64];
static Display *display;

/*
  TODOs
  - Handle basic commandline arguments
  - Add installation script (move to Make?)
  - Could always use more modules :)
*/

void cache_into_status()
{
    size_t t_len = 0;
    for(size_t i = 0; i < MODULES_LEN; ++i) {
        strncpy(status+t_len, cache[i], STATUS_MAX_LEN-t_len);
        t_len += strlen(cache[i]);
    }
}

void print_cache()
{
    for (size_t i = 0; i < MODULES_LEN; ++i) {
        printf("%s ", cache[i]);
    }
    putchar('\n');
}

int main()
{
    int ldelay = 1, timer = 0;

    if (!(display = XOpenDisplay(NULL))) {
        fputs("Error: failed to open X display. Is a graphical session running?", stderr);
        exit(1);
    }

    struct timespec refresh;
    refresh.tv_sec  = MIN_REFRESH_MS / 1000;
    refresh.tv_nsec = MIN_REFRESH_MS * 1000000L % 999999999L;

    /* cache initial values */
    for(size_t i = 0; i < MODULES_LEN; ++i) {
        strncpy(cache[i], modules[i].func(modules[i].arg), 64);
        if (modules[i].delay > ldelay) {
            ldelay = modules[i].delay;
        }
    }

    while(1) {
        for (size_t i = 0; i < MODULES_LEN; ++i) {
            if (timer % modules[i].delay == 0) {
                strncpy(cache[i], modules[i].func(modules[i].arg), 64);
            }
        }

        cache_into_status();
        // printf("[%d:%d] %s\n", timer, ldelay, status);

        if (!XStoreName(display, DefaultRootWindow(display), status)) {
            fputs("Error: failed to set root window name.", stderr);
            exit(1);
        }
        XFlush(display);
        
        timer = (timer + 1) % ldelay;
        nanosleep(&refresh, NULL);
    }

}
