# Adapted from https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/
CC=gcc

CFLAGS=`sdl2-config --libs --cflags` -Wall -lSDL2_image -lm
HDRS=player.h ball.h util.h

SRCS=main.c player.c ball.c util.c
OBJS=$(SRCS:.c=.o)

EXEC=pong

all: $(EXEC)
 
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean