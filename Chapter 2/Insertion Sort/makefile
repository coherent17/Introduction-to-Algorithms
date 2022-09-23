CC = gcc
CFLAGS = -g -Wall

BIN = insertion_sort

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN)