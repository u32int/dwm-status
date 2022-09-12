#!/bin/sh


if [ ! -f "./dwm-status" ]; then
    sh ./build.sh;
fi

set -x

sudo cp dwm-status /usr/local/bin/
sudo chmod +x /usr/local/bin/dwm-status
