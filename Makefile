CC=gcc
CFLAGS=-lX11 -std=c11 -Wall -Wextra
CFILES=main.c util.c modules.c

BIN=dwm-status
INSTALL_PATH=/usr/local/bin/

all: $(BIN)

$(BIN): $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(BIN)

install: $(BIN)
	chmod +x $(BIN) 
	sudo cp $(BIN) $(INSTALL_PATH)

clean:
	rm $(BIN)
