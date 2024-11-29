all: benchmark

CFLAGS += -g -Wall -Werror -pthread

%.o: %.c *.h
	gcc $(CFLAGS) -c -o $@ $<

benchmark: main.c
	gcc $(CFLAGS) main.c -o main