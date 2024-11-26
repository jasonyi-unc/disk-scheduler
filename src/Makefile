all: benchmark

CFLAGS += -g -Wall -Werror -pthread

%.o: %.c *.h
	gcc $(CFLAGS) -c -o $@ $<

benchmark: benchmark.c
	gcc $(CFLAGS) benchmark.c -o benchmark