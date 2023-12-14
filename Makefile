# Adapted from https://www.geeksforgeeks.org/sdl-library-in-c-c-with-examples/
CC=gcc
CPP=g++

ODIR=obj
EXEC=pong

# C flags and setup for SDL game
SDL=`sdl2-config --libs --cflags`
CFLAGS=$(SDL) -Wall
CLIB=-lSDL2_image -lm
HDRS=player.h ball.h util.h score.h

SRCS=main.c player.c ball.c util.c score.c
OBJS=$(patsubst %.c, $(ODIR)/%.o, $(SRCS))

# C++ flags and setup for ImGui UI elements
CPPLIB=-l glfw -l GLEW
ifdef MAC
CPPLIB+=-framework OpenGL
else
CPPLIB+=-l GL
endif

IMGUI_SRC=imgui.cpp imgui_draw.cpp imgui_widgets.cpp imgui_tables.cpp backends/imgui_impl_sdl2.cpp backends/imgui_impl_sdlrenderer2.cpp
IMGUI_OBJ=$(patsubst %.cpp, $(ODIR)/%.o, $(patsubst backends/%, %, $(IMGUI_SRC)))
IMGUI_FLAGS=-I imgui -I imgui/backends $(SDL)

all: $(EXEC)
	
makedir:
	mkdir -p $(ODIR)
	
imgui:
	$(CPP) -c $(IMGUI_FLAGS) $(patsubst %.cpp, imgui/%.cpp, $(IMGUI_SRC))
	mv imgui*.o $(ODIR)
	
$(ODIR)/%.o: %.c $(HDRS) makedir
	$(CC) $(CFLAGS) -c -o $@ $<
 
$(EXEC): $(OBJS) $(HDRS) imgui Makefile
	$(CPP) -o $@ $(OBJS) $(IMGUI_OBJ) $(CLIB) $(CPPLIB) $(SDL)

clean:
	rm -f $(EXEC) $(OBJS) $(IMGUI_OBJ)

.PHONY: all clean makedir imgui