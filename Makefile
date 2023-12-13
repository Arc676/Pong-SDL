# Adapted from https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/
CC=gcc

CFLAGS=`sdl2-config --libs --cflags` -Wall -lSDL2_image -lm
HDRS=player.h ball.h util.h score.h

SRCS=main.c player.c ball.c util.c score.c
ODIR=obj
OBJS=$(patsubst %.c, $(ODIR)/%.o, $(SRCS))

EXEC=pong

all: $(EXEC)
	
makedir:
	mkdir -p $(ODIR)
	
$(ODIR)/%.o: %.c $(HDRS) makedir
	$(CC) $(CFLAGS) -c -o $@ $<
 
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean makedir