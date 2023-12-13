# Adapted from https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/
CC=g++

CFLAGS=`sdl2-config --libs --cflags` -Wall -lSDL2_image -lm
HDRS=

SRCS=main.cpp
OBJS=$(SRCS:.c=.o)

EXEC=pong

all: $(EXEC)
 
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean