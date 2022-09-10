#include <stddef.h>
#include "modules.h"

#define STATUS_MAX_LEN 256
#define MIN_REFRESH_MS 999

/*
  Modules have three fields:
    1. the function pointer
    2. arg
    3. delay/refresh rate = n * MIN_REFRESH_MS (so seconds by default)
 If the delay is a negative number, the function will only be executed once and the module
 will not be 'refreshed'. Useful for static text modules or kernel versions.

 module       arg

 text         The text to display.
 color_fg     Hex color code 
 color_bg     Hex color code 
 color_bg     NULL/unused 

 time         strftime time format - read 'man 3 strftime'
 loadavg      NULL
*/

static const struct module modules[] = {
    {load_avg, NULL,              2},
    {text,     " ",              -1},
    {text,     "sample text ",   -1},
    {color_fg, "#ffffff",        -1},
    {text,     "[",              -1},
    {datetime, "%d/%b/%Y %H:%M",  1},
    {text,     "]",              -1},
};

#define MODULES_LEN (sizeof(modules) / sizeof(modules[0]))
