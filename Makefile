CC = clang
CFLAGS = -Wall -Wextra -Wpedantic -g

SRC_DIR = src
SERVER_SRC = $(SRC_DIR)/server.c
CLIENT_SRC = $(SRC_DIR)/client.c

SERVER_BIN = server
CLIENT_BIN = client

all: $(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN): $(SERVER_SRC)
	$(CC) $(CFLAGS) $< -o $@

$(CLIENT_BIN): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(SERVER_BIN) $(CLIENT_BIN)

