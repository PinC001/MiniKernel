CC = gcc
CFLAGS = -Wall -Iinclude
LIBS = -lpthread

SRCS = src/main.c src/queue.c src/cpu.c src/metrics.c
OBJS = $(SRCS:.c=.o)

minikernel: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o minikernel $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: rm -f src/*.o minikernel
