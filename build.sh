#!/bin/sh

CFLAGS="-lX11 -std=c11 -Wall -Wextra"

set -xe

gcc main.c modules.c util.c $CFLAGS -o dwm-status
