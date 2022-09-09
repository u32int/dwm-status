#!/bin/sh

CFLAGS="-lX11 -std=c11 -Wall -Wextra"

set -xe

gcc main.c modules.c $CFLAGS -o dwm-status
