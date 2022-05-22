CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: main

main: main.cpp timers.cpp ui.cpp entity.cpp
	g++ $(CFLAGS) main.cpp timers.cpp ui.cpp entity.cpp -Wall -Wextra $(LFLAGS) -osoul_terrain

clean:
	rm -f soul_terrain
	rm -f *.o
