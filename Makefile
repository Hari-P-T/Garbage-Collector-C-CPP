CC = gcc
CFLAGS = -Wall -pthread -Iinclude
SRC = src/collector.c
TARGET = test/collector_test

all: $(TARGET)

$(TARGET): test/main.c $(SRC)
	$(CC) $(CFLAGS) test/main.c $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
