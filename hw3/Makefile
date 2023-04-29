#
# Makefile
#
# Computer Science 50
# Problem Set 3
#

CC = gcc
CFLAGS = -g
OBJS = fifteen

fifteen: fifteen.c
	$(CC) $(CFLAGS) -std=c11 -Wall -o $(OBJS) $< -lm

clean:
	rm -f *.o a.out core fifteen log.txt